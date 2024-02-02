/*
 * Copyright 1993-2010 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */

// standard utilities and systems includes
#include <iostream>
#include <cassert>
#include "BlackScholes_common_mt3000.h"
#include "hthread_host.h"


////////////////////////////////////////////////////////////////////////////////
// Random float helper
////////////////////////////////////////////////////////////////////////////////
float randFloat(float low, float high){
    float t = (float)rand() / (float)RAND_MAX;
    return (1.0f - t) * low + t * high;
}
#include <time.h>
#include <sys/time.h>
long long get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

static inline
uint64_t doubleToRawBits(double x){
    union{
        uint64_t i;
        double f;
    }word;
    word.f = x;
    return word.i;
}

static inline
uint32_t floatToRawBits(float x){
    union{
        uint32_t i;
        float f;
    }word;
    word.f = x;
    return word.i;
}

int BlackScholesMT3000(int clusterId, \
                         char *kernel,\
                       float *d_Call, \
                        float *d_Put, \
                          float *d_S, \
                          float *d_X, \
                          float *d_T, \
                             float R, \
                             float V, \
             unsigned int optionCount){
    uint64_t args[8];
    args[0] = (uint64_t)optionCount;
    args[1] = (uint64_t)floatToRawBits(R);
    args[2] = (uint64_t)floatToRawBits(V);
    args[3] = (uint64_t)d_Call;
    args[4] = (uint64_t)d_Put;
    args[5] = (uint64_t)d_S;
    args[6] = (uint64_t)d_X;
    args[7] = (uint64_t)d_T;
    int threadsID = hthread_group_create(clusterId, 20, kernel, 3, 5, args);
    hthread_group_wait(threadsID);
    return threadsID;
}

////////////////////////////////////////////////////////////////////////////////
// Main program
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
        unsigned int scale = 200;
        int clusterId = 0;
        char *devProgram = (char *)"./bsKernel.dev.dat";
        if(argc >  1){
            scale = atoi(argv[1]);
        }
        if(argc > 2){
            clusterId = atoi(argv[2]);
        }
        if(argc > 3){
            devProgram = argv[3];
        }
        fprintf(stdout, "scale : %u, clusterId : %d, devProgram : %s\n",\
                             scale, clusterId, devProgram);fflush(stdout);
        //
        int htStat = HT_SUCCESS;
        htStat = hthread_dev_open(clusterId);
        assert(HT_SUCCESS == htStat);
        htStat = hthread_dat_load(clusterId, devProgram);
        assert(HT_SUCCESS == htStat);
        //
        float
            *h_CallCPU,
            *h_PutCPU,
            *h_S,
            *h_X,
            *h_T;

        const unsigned int   optionCount = 40000 * scale;
        //const unsigned int   optionCount = 4000000 * 10;
        const float                    R = 0.02f;
        const float                    V = 0.30f;


        h_CallCPU = (float *)malloc(optionCount * sizeof(float));
        h_PutCPU  = (float *)malloc(optionCount * sizeof(float));
        h_S       = (float *)malloc(optionCount * sizeof(float));
        h_X       = (float *)malloc(optionCount * sizeof(float));
        h_T       = (float *)malloc(optionCount * sizeof(float));

        float *h_CallCPU_S = (float *)malloc(sizeof(float) * optionCount);
        float *h_PutCPU_S  = (float *)malloc(sizeof(float) * optionCount);

        //
        float *d_Call    = (float *)hthread_malloc(clusterId, \
                        optionCount * sizeof(float), HT_MEM_RW);
        float *d_Put     = (float *)hthread_malloc(clusterId, \
                        optionCount * sizeof(float), HT_MEM_RW);
        float *d_S       = (float *)hthread_malloc(clusterId, \
                        optionCount * sizeof(float), HT_MEM_RW);
        float *d_X       = (float *)hthread_malloc(clusterId, \
                        optionCount * sizeof(float), HT_MEM_RW);
        float *d_T       = (float *)hthread_malloc(clusterId, \
                        optionCount * sizeof(float), HT_MEM_RW);
        //

        srand(2009);
        for(unsigned int i = 0; i < optionCount; i++){
            h_CallCPU[i] = -1.0f;
            h_PutCPU[i]  = -1.0f;
            h_CallCPU_S[i] = -1.0f;
            h_PutCPU_S[i]  = -1.0f;
            h_S[i]       = randFloat(5.0f, 30.0f);
            h_X[i]       = randFloat(1.0f, 100.0f);
            h_T[i]       = randFloat(1.25f, 10.0f);
            //
            d_Call[i]    = -1.0f;
            d_Put[i]     = -1.0f;
            d_S[i]       = h_S[i];
            d_X[i]       = h_X[i];
            d_T[i]       = h_T[i];
        }


///////////////////////////////////////////////////////////////////////////////
        double cpuTime = get_time();
        BlackScholesCPU(h_CallCPU_S, h_PutCPU_S, h_S, h_X, h_T, R, V, optionCount);
        cpuTime = ((double)(get_time() - cpuTime));

        double devTime = get_time();
        int threadsID = BlackScholesMT3000(clusterId, (char *)"BlackScholesthreads", \
                            d_Call, d_Put, d_S, d_X, d_T, R, V, optionCount);
        devTime = ((double)get_time() - devTime);
        hthread_group_destroy(threadsID);
        int stat = Compare_Result(optionCount, d_Call, d_Put, h_CallCPU_S, h_PutCPU_S);
        if(stat != 0){
            fprintf(stderr, "Faild   : Error in Result Compare \n");
            fflush(stderr);
        }else{
            fprintf(stdout, "Success : Result Compare is OK \n");
            fprintf(stdout, \
            "Profile : CpuTime : %lfus, %lfs \nProfile : devTime : %lfus, %lfs\n",\
             cpuTime, cpuTime/(1000000),devTime, devTime/(1000000));
        }

        free(h_CallCPU_S);free(h_PutCPU_S);
        free(h_CallCPU);free(h_PutCPU);
        free(h_S);
        free(h_X);
        free(h_T);
        //
        hthread_free(d_Call);
        hthread_free(d_Put );
        hthread_free(d_S   );
        hthread_free(d_X   );
        hthread_free(d_T   );
        hthread_dat_unload(clusterId);
        hthread_dev_close(clusterId);
        //

    return stat;
}
