#include <stdint.h>

#include <compiler/m3000.h>
#include "hthread_device.h"
#define M_MT_CacheNum 1024


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
    //daxpy_kernel(n_p,a,x+offset,y+offset);
    daxpy_singe(n_p,a,x+offset,y+offset);
    
}

__global__
void daxpy_singe(uint64_t n, double a, double *x, double *y){

    double x_cache[M_MT_CacheNum];
    double y_cache[M_MT_CacheNum];
    uint64_t n_cache = M_MT_CacheNum;
    uint64_t n_actual = 0;
    uint64_t i=0;
    for(i=0;i<n;i+=n_actual){
        n_actual=(n-i) >= n_actual ? n_cache : (n-i);
        uint64_t size_actual =n_actual * sizeof(double);
        scalar_load(x+i,x_cache, size_actual);
        scalar_load(y+i,y_cache, size_actual);
        daxpy_kernel(n_actual,a,x_cache,y_cache);
        scalar_store(y_cache,y+i,size_actual);
    }
}