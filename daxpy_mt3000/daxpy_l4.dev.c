/**
 * daxpy.hos.c
 * @Author      : jshen, longbiao  
 * @Date        : 2022-06-27 
 * @Project     : MT3000 daxpy
 * @description : example implementation of daxpy on MT3000
 *                y = x * alph + y 
 * 
**/
#include <stdint.h>

#include <compiler/m3000.h>
#include "hthread_device.h"


//static inline
void daxpy_cache(uint64_t n,  \
            lvector double a, \
           lvector double *x, \
           lvector double *y){
    uint64_t i = 0;
#if 0
    for (i = 0; i < n; i += 2){
        lvector double x_vec_0 = vec_ld(0, x + i + 0);
        lvector double x_vec_1 = vec_ld(0, x + i + 1);
        lvector double y_vec_0 = vec_ld(0, y + i + 0);
        lvector double y_vec_1 = vec_ld(0, y + i + 1);
        y_vec_0 = vec_mula(x_vec_0, a, y_vec_0);
        y_vec_1 = vec_mula(x_vec_1, a, y_vec_1);
        vec_st(y_vec_0, 0, y + i + 0);
        vec_st(y_vec_1, 0, y + i + 1);
    }
#endif
#if 0
    for (i = 0; i < n; i += 4){
        lvector double x_vec_0 = vec_ld(0, x + i + 0);
        lvector double x_vec_1 = vec_ld(0, x + i + 1);
        lvector double x_vec_2 = vec_ld(0, x + i + 2);
        lvector double x_vec_3 = vec_ld(0, x + i + 3);
        lvector double y_vec_0 = vec_ld(0, y + i + 0);
        lvector double y_vec_1 = vec_ld(0, y + i + 1);
        lvector double y_vec_2 = vec_ld(0, y + i + 2);
        lvector double y_vec_3 = vec_ld(0, y + i + 3);
        y_vec_0 = vec_mula(x_vec_0, a, y_vec_0);
        y_vec_1 = vec_mula(x_vec_1, a, y_vec_1);
        y_vec_2 = vec_mula(x_vec_2, a, y_vec_2);
        y_vec_3 = vec_mula(x_vec_3, a, y_vec_3);
        vec_st(y_vec_0, 0, y + i + 0);
        vec_st(y_vec_1, 0, y + i + 1);
        vec_st(y_vec_2, 0, y + i + 2);
        vec_st(y_vec_3, 0, y + i + 3);
    }
#endif
#if 0
    for (i = 0; i < n; i += 8){
        lvector double x_vec_0 = vec_ld(0, x + i + 0);
        lvector double x_vec_1 = vec_ld(0, x + i + 1);
        lvector double x_vec_2 = vec_ld(0, x + i + 2);
        lvector double x_vec_3 = vec_ld(0, x + i + 3);
        lvector double x_vec_4 = vec_ld(0, x + i + 4);
        lvector double x_vec_5 = vec_ld(0, x + i + 5);

        lvector double y_vec_0 = vec_ld(0, y + i + 0);
        lvector double y_vec_1 = vec_ld(0, y + i + 1);
        lvector double y_vec_2 = vec_ld(0, y + i + 2);
        lvector double y_vec_3 = vec_ld(0, y + i + 3);
        lvector double y_vec_4 = vec_ld(0, y + i + 4);
        lvector double y_vec_5 = vec_ld(0, y + i + 5);
        y_vec_0 = vec_mula(x_vec_0, a, y_vec_0);
        y_vec_1 = vec_mula(x_vec_1, a, y_vec_1);
        y_vec_2 = vec_mula(x_vec_2, a, y_vec_2);
        y_vec_3 = vec_mula(x_vec_3, a, y_vec_3);
        y_vec_4 = vec_mula(x_vec_4, a, y_vec_4);
        y_vec_5 = vec_mula(x_vec_5, a, y_vec_5);
        vec_st(y_vec_0, 0, y + i + 0);
        vec_st(y_vec_1, 0, y + i + 1);
        vec_st(y_vec_2, 0, y + i + 2);
        vec_st(y_vec_3, 0, y + i + 3);
        vec_st(y_vec_4, 0, y + i + 4);
        vec_st(y_vec_5, 0, y + i + 5);
    }
#endif
#if 1
    for (i = 0; i < n; i += 8){
        lvector double x_vec_0 = vec_ld(0, x + i + 0);
        lvector double x_vec_1 = vec_ld(0, x + i + 1);
        lvector double x_vec_2 = vec_ld(0, x + i + 2);
        lvector double x_vec_3 = vec_ld(0, x + i + 3);
        lvector double x_vec_4 = vec_ld(0, x + i + 4);
        lvector double x_vec_5 = vec_ld(0, x + i + 5);
        lvector double x_vec_6 = vec_ld(0, x + i + 6);
        lvector double x_vec_7 = vec_ld(0, x + i + 7);

        lvector double y_vec_0 = vec_ld(0, y + i + 0);
        lvector double y_vec_1 = vec_ld(0, y + i + 1);
        lvector double y_vec_2 = vec_ld(0, y + i + 2);
        lvector double y_vec_3 = vec_ld(0, y + i + 3);
        lvector double y_vec_4 = vec_ld(0, y + i + 4);
        lvector double y_vec_5 = vec_ld(0, y + i + 5);
        lvector double y_vec_6 = vec_ld(0, y + i + 6);
        lvector double y_vec_7 = vec_ld(0, y + i + 7);
        y_vec_0 = vec_mula(x_vec_0, a, y_vec_0);
        y_vec_1 = vec_mula(x_vec_1, a, y_vec_1);
        y_vec_2 = vec_mula(x_vec_2, a, y_vec_2);
        y_vec_3 = vec_mula(x_vec_3, a, y_vec_3);
        y_vec_4 = vec_mula(x_vec_4, a, y_vec_4);
        y_vec_5 = vec_mula(x_vec_5, a, y_vec_5);
        y_vec_6 = vec_mula(x_vec_6, a, y_vec_6);
        y_vec_7 = vec_mula(x_vec_7, a, y_vec_7);
        vec_st(y_vec_0, 0, y + i + 0);
        vec_st(y_vec_1, 0, y + i + 1);
        vec_st(y_vec_2, 0, y + i + 2);
        vec_st(y_vec_3, 0, y + i + 3);
        vec_st(y_vec_4, 0, y + i + 4);
        vec_st(y_vec_5, 0, y + i + 5);
        vec_st(y_vec_6, 0, y + i + 6);
        vec_st(y_vec_7, 0, y + i + 7);
    }
#endif
    for (;i < n; i += 1){
        lvector double x_vec = vec_ld(0, x + i);
        lvector double y_vec = vec_ld(0, y + i);
        y_vec = vec_mula(x_vec, a, y_vec);
        vec_st(y_vec, 0, y + i);
    }
}

//vector align
#define M_MT_CacheNum (2048) // (2048 * 16 * 8) / 1024 = 256KB
#define M_MT_VecLen   (16)

static inline
void daxpy_single(uint64_t n, double a, double *x, double *y){
    uint64_t n_cache = M_MT_CacheNum * M_MT_VecLen;
    //malloc cache memory
    lvector double *x_cache = (lvector double *)vector_malloc(\
                                     n_cache * sizeof(double));
    lvector double *y_cache = (lvector double *)vector_malloc(\
                                     n_cache * sizeof(double));
    //
    uint64_t n_actual = 0;
    uint64_t i = 0;
    for( i = 0; i < n; i += n_actual){
        n_actual = (n - i) >= n_cache ? n_cache : (n - i);
        uint64_t size_actual = n_actual * sizeof(double);
        vector_load(x + i, x_cache, size_actual);
        vector_load(y + i, y_cache, size_actual);
        uint64_t vLen = n_actual / M_MT_VecLen;
        vLen = ((n_actual % M_MT_VecLen) == 0) ? vLen : (vLen + 1);
	lvector double a_vec = vec_svbcast(a);	
        daxpy_cache(vLen, a_vec, x_cache, y_cache);
        vector_store(y_cache, y + i, size_actual);
    }
    // free cache memory
    vector_free(x_cache);
    vector_free(y_cache);
}

__global__
void daxpy_kernel(uint64_t n, double a, double *x, double *y){
    int threadId = get_thread_id();
    int threadsNum = get_group_size();
    if(threadId >= threadsNum) return;
    uint64_t n_p = n / threadsNum;
    uint64_t extras = n % threadsNum;
    uint64_t offset;
    if(threadId < extras) {
        n_p++;
        offset = threadId * n_p;
    }else{
        offset = threadId * (n_p + 1) - (threadId - extras);
    }
    daxpy_single(n_p, a, x + offset, y + offset);
}
