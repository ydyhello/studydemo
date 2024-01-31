#include <compiler/m3000.h>
#include "hthread_device.h"
/*
 * copy - native version
 * */
__global__ void  native_copy(unsigned long length,
		unsigned long coreNum,
		long *A,
		long *C)
{
	int tid = get_thread_id();
	long i = 0;
	unsigned long offset = tid * length;
	long *A_fixed = &A[offset];
	long *C_fixed = &C[offset];

	hthread_printf("[Core %d] Start copy\n", tid);
	for (i = 0; i < length; i ++)
		C_fixed[i] = A_fixed[i];
}
