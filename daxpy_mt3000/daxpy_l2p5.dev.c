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


static inline
void daxpy_cache(uint64_t n, double a, double *x, double *y){
    for (uint64_t i = 0; i < n; ++i){
        y[i] = a * x[i] + y[i];
    }
}

#define M_MT_CacheNum 1024 // (1024 * 8) / 1024 = 8KB


typedef struct{
    uint64_t offset;
    uint64_t n_actual;
    double *x_cache;
    double *y_cache;
    double *x;
    double *y;
}Job;


static inline
void initJobs(Job *jobs, uint64_t num, double *x, double *y){
    for(uint64_t i = 0; i < num; i++){
        jobs[i].x = x;
        jobs[i].y = y;
    }
}

static inline
void Job_set(Job *job, uint64_t offset, uint64_t n_actual){
    job->offset = offset;	
    job->n_actual = n_actual;
}
static inline
void Job_setCache(Job *job, double *x_cache, double *y_cache){
    job->x_cache = x_cache;
    job->y_cache = y_cache;
}

static inline
void daxpy_single(uint64_t n, double a, double *x, double *y){
    //malloc cache memory
    double x_caches[3][M_MT_CacheNum];
    double y_caches[3][M_MT_CacheNum];
    uint64_t n_cache = M_MT_CacheNum;
    uint64_t n_actual = 0;
    Job jobs[3];
    Job *loadJob = NULL, *storeJob = NULL, *daxpyJob = NULL;
    unsigned int ldxc = 0, ldyc = 0, styc = 0;
    uint64_t i = 0, c = 0;
    for(i = 0; i < n; i += n_actual){
        // create new job
        n_actual = (n - i) >= n_cache ? n_cache : (n - i);
        uint64_t no = c % 3;
        Job_set(jobs + no, i, n_actual);
        loadJob = jobs + no;
        // exec job
        if(loadJob != NULL){
            Job_setCache(loadJob, x_caches[c % 3], y_caches[c % 3]);
            uint64_t offset   = loadJob->offset;
            uint64_t n_actual = loadJob->n_actual;
            double *x_cache   = loadJob->x_cache;
            double *y_cache   = loadJob->y_cache;
            ldxc = scalar_load_async(x + offset, x_cache, n_actual * sizeof(double));
            ldyc = scalar_load_async(y + offset, y_cache, n_actual * sizeof(double));
        }
        if(storeJob !=NULL){
            uint64_t offset = storeJob->offset;
            uint64_t n_actual = storeJob->n_actual;
            double *y_cache = storeJob->y_cache;
            styc = scalar_store_async(y_cache, y + offset, n_actual * sizeof(double));
        }
        if(daxpyJob != NULL){
            uint64_t n_actual = daxpyJob->n_actual;
            double *x_cache = daxpyJob->x_cache;
            double *y_cache = daxpyJob->y_cache;
            daxpy_cache(n_actual, a, x_cache, y_cache);
        }
        // wait
        if(loadJob != NULL) {dma_wait(ldxc);dma_wait(ldyc);}
        if(storeJob != NULL) dma_wait(styc);
        // pipeline
        if(storeJob != NULL){
            storeJob = NULL;
        }
        if(daxpyJob != NULL){
            storeJob = daxpyJob;daxpyJob = NULL;
        }
        if(loadJob != NULL){
            daxpyJob = loadJob;loadJob = NULL;
        }
        c++;
    }
    //tail : last storeJob and last daxpyJob
    if(storeJob != NULL){
        scalar_store(storeJob->y_cache, y + (storeJob->offset), \
                        sizeof(double) * (storeJob->n_actual));
    }
    if(daxpyJob != NULL){
        daxpy_cache(daxpyJob->n_actual, a, \
                         daxpyJob->x_cache, daxpyJob->y_cache);
        scalar_store(daxpyJob->y_cache, y + (daxpyJob->offset), \
                        sizeof(double) * (daxpyJob->n_actual));
    }
    storeJob = NULL;daxpyJob = NULL;
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
