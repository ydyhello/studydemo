#include <stdint.h>

#include <compiler/m3000.h>
#include "hthread_device.h"
#define M_MT_CacheNum 64
#define M_MT_VecLen 16


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
    uint64_t n_cache =M_MT_CacheNum * M_MT_VecLen;
    lvector double *x_cache=(lvector double *)vector_malloc(n_cache*sizeof(double));
    lvector double *y_cache=(lvector double *)vector_malloc(n_cache*sizeof(double));
    uint64_t n_actual = 0;
    lvector double a_vec =vec_svbcast(a);
    for(uint64_t i=0;i<n;i+=n_actual){
        n_actual=(n-i) >= n_actual ? n_cache : (n-i);
        uint64_t size_actual =n_actual * sizeof(double);
        vector_load(x+i,x_cache,size_actual);
        vector_load(y+i,y_cache,size_actual);
        uint64_t vLen =n_actual / M_MT_VecLen;
        vLen=((n_actual % M_MT_VecLen)==0) ? vLen :(vLen + 1);
        daxpy_cache(vLen, a_vec,x_cache,y_cache);
        vector_store(y_cache,y+i, size_actual);
    }
    vector_free(x_cache);
    vector_free(y_cache);

}


__global__
void daxpy_cache(uint64_t n, lvector double a, lvector double *x, lvector double *y)
{
    uint64_t i=0;
    for(i = 0; i < n; i += 2){
        lvector double x_vec_0=vec_ld(0,x+i+0);
        lvector double x_vec_1=vec_ld(0,x+i+1);
        lvector double y_vec_0=vec_ld(0,y+i+0);
        lvector double y_vec_1=vec_ld(0,y+i+1);
        y_vec_0=vec_mula(x_vec_0,a,y_vec_0);
        y_vec_1=vec_mula(x_vec_1,a,y_vec_1);
        vec_st(y_vec_0,0,y+i+0);
        vec_st(y_vec_1,0,y+i+1);
    }
    //TODO:tail处理

}