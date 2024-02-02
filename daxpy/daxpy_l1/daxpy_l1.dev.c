#include <stdint.h>

#include <compiler/m3000.h>
#include "hthread_device.h"

__global__
void daxpy_kernel(uint64_t n, double a, double *x, double *y){
    for (uint64_t i = 0; i < n; ++i){
        y[i] = a * x[i] + y[i];
    }
}

__global__
void daxpy_threads(uint64_t n, double a, double *x, double *y){
    int threadId = get_thread_id();
    int threadsNum = get_group_size();
    uint64_t n_p = n/threadsNum;
    uint64_t extras = n%threadsNum;
    uint64_t offset;
    if(threadId < extras){
        n_p++;
        offset=threadId*n_p;
    }else{
        offset=threadId*(n_p+1)-(threadId-extras);
    }
    daxpy_kernel(n_p,a,x+offset,y+offset);
}