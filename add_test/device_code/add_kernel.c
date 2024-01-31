
#include <compiler/m3000.h>
#include "hthread_device.h"
/*
 * copy - native version
 * */
__global__ void  native_copy(unsigned long length,
		unsigned long coreNum,
		long *A,
    long *B,
		long *C)
{
	int tid = get_thread_id();
	long i = 0;
	unsigned long offset = tid * length;
	long *A_fixed = &A[offset];
  long *B_fixed = &B[offset];
	long *C_fixed = &C[offset];
 
   unsigned long t1=0,t2=0,t3=0,t4=0,t5 =0;
  int thidx= get_thread_id();
  t1 = get_clk();
  
  

	hthread_printf("[Core %d] Start add\n", tid);
	for (i = 0; i < length; i ++)
     //C_fixed[i] = A_fixed[i];
		C_fixed[i] = A_fixed[i] + B_fixed[i];
   
   t2 = get_clk();
   
   hthread_printf("[Core %d] t1 = %lu\n", tid, t1);
   hthread_printf("[Core %d] t2 = %lu\n", tid, t2);
   


}
