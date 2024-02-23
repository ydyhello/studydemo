/**
 * daxpy.hos.c
 * @Author      : jshen, longbiao  
 * @Date        : 2022-06-27 
 * @Project     : MT3000 daxpy
 * @description : example implementation of daxpy on MT3000
 *                y = x * alph + y 
 * 
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>	

#include "hthread_host.h"

uint64_t doubleToRawBits(double d) {
    union{
        uint64_t i;
        double f;
    } word;
    word.f = d;
    return word.i;
}

void daxpy_cpu(int n, double a, double *x, double *y){
    for (int i = 0; i < n; ++i){
        y[i] = a * x[i] + y[i];
    }
}

int check_daxpy(int n, double *y_gold, double *y){
    int errNum = 0;
    for (int i = 0; i < n; ++i){
        if(y[i] != y_gold[i]){
            fprintf(stderr, "%d-data error : %le != %le\n",\
					 i, y[i], y_gold[i]);
            errNum++;
            if(errNum >= 100) break;
        }
    }
    return errNum;
}

uint64_t getCurrentTimeMicros() {
  struct timeval time;
  gettimeofday(&time, NULL);
  return (uint64_t)((time.tv_sec * INT64_C(1000000)) + time.tv_usec);
}

int fileIsExist(const char *filePath){
    return access(filePath, F_OK);
}

#define M_logError(_FMT,...)\
do{\
    fprintf(stderr, "Error : " _FMT "in %d of %s\n", \
          __VA_ARGS__, __LINE__, __FILE__);\
}while(0);

#define M_checkRetC(_RETC, _MSG)\
do{\
    if(_RETC != HT_SUCCESS){\
        fprintf(stderr, "Failed to exec %s in %d of %s : %d\n", \
                                  #_MSG, __LINE__, __FILE__, _RETC);\
        return 2;\
    }\
}while(0);

#define M_checkMalloc(_PTR)\
do{\
    if(_PTR == NULL){\
        fprintf(stderr, "Failed to malloc %s in %d of %s\n", \
                                    #_PTR, __LINE__, __FILE__);\
        return 2;\
    }\
}while(0);

int main(int argc, char **argv){
    int retc;
    int clusterId = 0;
    int n = 1024 * 1024 * 100;
    double alph = 3.14;
    char *devProgram = "./daxpy.dev.dat";
    int nthreads = 1;
    char *kernel = "daxpy_kernel";
    uint64_t timeGold, timeDev;
    //
    if(argc > 1){
        clusterId = atoi(argv[1]);
    }
    if(argc > 2){
        n = atoi(argv[2]);
    }
    if(argc > 3){
        alph = (double)atof(argv[3]);
    }
    if(argc > 4){
        devProgram = argv[4];
    }
    if(argc > 5){
        nthreads = atoi(argv[5]);
    }
    fprintf(stdout, "clusterId : %d, n : %d, alph : %le, "\
                      "devProgram : %s, nthreads : %d\n", \
                 clusterId, n, alph, devProgram, nthreads);
    
    // check args
    if(clusterId < 0 || clusterId > 3){
        M_logError("invalid clusterId : %d", clusterId);
        return 2;
    }
    if(nthreads <= 0){
        M_logError("invalid nthreads : %d", nthreads);
        return 2;
    }
    if(fileIsExist(devProgram) != 0){
        M_logError("%s : No such file or directory", devProgram);
        return 2;
    }
    

    // device init
    retc = hthread_dev_open(clusterId);
    M_checkRetC(retc, hthread_dev_open);
    retc = hthread_dat_load(clusterId, devProgram); 
    M_checkRetC(retc, hthread_dat_load);
    int availThreads = hthread_get_avail_threads(clusterId);
    if(nthreads > availThreads){
        M_logError("number of threads is overflow : avail threads is %d, "\
                            "actual threads is %d", availThreads, nthreads);
        retc = hthread_dat_unload(clusterId); 
        retc = hthread_dev_close(clusterId);
        return 2;
    }

    // malloc
    size_t bufSize = (size_t)n * sizeof(double);
    double *x = (double *)hthread_malloc(clusterId, bufSize, HT_MEM_RO);
    M_checkMalloc(x);
    double *y = (double *)hthread_malloc(clusterId, bufSize, HT_MEM_RO);
    M_checkMalloc(y);
    double *y_gold = (double *)malloc(bufSize);
    M_checkMalloc(y_gold);

    // init data
    size_t i = 0;
    for(i = 0; i < (size_t)n; i++){
        x[i] = 0.0 + 1.0 * rand() / RAND_MAX * (6.28 - 0.0);
        y[i] = 0.0;
        y_gold[i] = 0.0;
    }  

    // launch dev kernel
    fprintf(stdout, "launch kernel : %s(%d, %lf, x, y)\n", \
                                            kernel, n, alph);
    fflush(stdout); 
    uint64_t args[4]; 
    args[0] = (uint64_t)n;
    args[1] = (uint64_t)doubleToRawBits(alph);
    args[2] = (uint64_t)x;
    args[3] = (uint64_t)y;
    timeDev = getCurrentTimeMicros();
    int threadId = hthread_group_create(clusterId, nthreads, \
                                   kernel, 1, 3, args);
    if(threadId == -1){
        M_logError("Failed to create threads with %s", kernel);
        return 2;
    }
    hthread_group_wait(threadId);
    timeDev = getCurrentTimeMicros() - timeDev;

    // gold and check
    timeGold = getCurrentTimeMicros();
    daxpy_cpu(n, alph, x, y_gold);
    timeGold = getCurrentTimeMicros() - timeGold;
    int errNum = check_daxpy(n, y_gold, y);    
    
    // fini
    hthread_group_destroy(threadId);
    if(x != NULL) hthread_free(x);
    if(y != NULL) hthread_free(y);
    if(y_gold != NULL) free(y_gold);
    retc = hthread_dat_unload(clusterId); 
    M_checkRetC(retc, hthread_dat_unload);
    hthread_dev_close(clusterId);
    M_checkRetC(retc, hthread_dev_close);

    //output result
    if(errNum != 0){
        fprintf(stderr, "Failed to test daxpy!\n");
        return 1;
    }else{
        fprintf(stdout, "daxpy passed!\n");
	fprintf(stdout, "WallTime of daxpy_kernel : %lu\n", timeDev);
	fprintf(stdout, "WallTime of daxpy_cpu    : %lu\n", timeGold);
        return 0;
    }
}
