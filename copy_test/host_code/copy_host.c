#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include "hthread_host.h"

#define NUM_CORES 24
#define NUM_TESTS 1

int main(int argc, char **argv){

	if (argc < 4) {
		printf("Useage: ~ dev_id{0, 1, 2, 3} length num_threads{1...24}\n");
		return -1;
	}

	int dev_id= atoi(argv[1]);
	long length = ((atol(argv[2]) +15)/ 16) * 16;
	int num_threads  = atoi(argv[3]);

	long size = length * num_threads * sizeof (long);
	long total_len = length * num_threads;

	hthread_dev_open(dev_id);
	hthread_dat_load(dev_id, "copy_kernel.dat");

	long *A = hthread_malloc(dev_id, size, HT_MEM_RO);
	long *C = hthread_malloc(dev_id, size, HT_MEM_RO);
	long *C_ref = malloc(size);

	for(int i=0;i<total_len;i++)
	{
		A[i]= i;
		C[i] = 0;
		C_ref[i] = A[i];
	}

	unsigned long args[4];
	args[0] = length;
	args[1] = num_threads;
	args[2] = (unsigned long)A;
	args[3] = (unsigned long)C;

	int tg_id = hthread_group_create(dev_id, num_threads);
	hthread_group_wait(tg_id);

	for(int i=0; i<NUM_TESTS; i++){
		hthread_group_exec(tg_id, "native_copy", 2, 2, args);
		hthread_group_wait(tg_id);

	}

	int error_num = 0;
#pragma omp parallel for reduction(+:error_num) num_threads(8)
	for(long i=0;i<total_len;i++) 	{
		if (C[i] != C_ref[i]) {
			//printf("C[%ld] = %ld\tC_ref[%ld] = %ld\n", i, C[i], i, C_ref[i]); 
			error_num ++;
		}
	}
	if (error_num > 0)
		printf("Result Error!\n");
	else 
		printf("Success!\n");


	hthread_group_destroy(tg_id);
	hthread_free(A);
	hthread_free(C);
	hthread_dev_close(dev_id);
	free(C_ref);

	return 0;
	}
