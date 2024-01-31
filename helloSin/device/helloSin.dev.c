#include <compiler/m3000.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "hthread_device.h"
#include "vector_math.h"

__global__ void kernel_evaluSin(uint64_t len,uint64_t coreNum,\
                                  double *optBuf,double *resBuf)
{   
    int core_id = get_thread_id();
    uint64_t offset = core_id * len;
    double *optBuf_fix = &optBuf[offset];
    double *resBuf_fix = &resBuf[offset];

    size_t dataNum = (16 * 1000 + 345 ) * 24 + 13;
    //lvector double *cache=(lvector double *)vector_malloc(cacheSize);
    lvector double * src1 = vector_malloc(len*sizeof(double));
    lvector double * src2 = vector_malloc(len*sizeof(double));
    
    vector_load(optBuf_fix,src1,len*sizeof(double));
    
    long i = 0;
    for(i = 0; i < dataNum/16; i++){
        src1[i] = (double)((i % 10000) - 5000);
        src2[i] = vm_asind16_u10(src1[i]);
    }

    vector_store(src2,resBuf_fix,len*sizeof(double));


    vector_free(src1);
	vector_free(src2);

}