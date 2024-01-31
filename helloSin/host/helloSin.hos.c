#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "hthread_host.h"
#define  CORE_NUM 1

typedef union
{
  uint64_t i;
  double f;
} number_double;

typedef union
{
  uint32_t i;
  float f;
} number_float;

static inline  uint64_t doubleToRawBits(double d) {
  number_double tmp;
  tmp.f = d;
  return tmp.i;
}
static inline  double rawBitsToDouble(uint64_t i) {
  number_double tmp;
  tmp.i = i;
  return tmp.f;
}
static inline  uint32_t floatToRawBits(float d) {
  number_float tmp;
  tmp.f = d;
  return tmp.i;
}
static inline  float rawBitsToFloat(uint32_t i) {
  number_float tmp;
  tmp.i = i;
  return tmp.f;
}

//check ulp
int comBuf_f64(double *optBuf, double *resBufH, double *resBufD, size_t bufLen, uint64_t maxDiff){
    size_t i;
    size_t errNum = 0;
    for(i = 0; i < bufLen; i++){
        double resH = resBufH[i];
        double resD = resBufD[i];
        uint64_t reResH = doubleToRawBits(resH);
        uint64_t reResD = doubleToRawBits(resD);
        uint64_t diff =  reResH > reResD ? reResH - reResD : reResD - reResH;
        if(diff >= maxDiff){
            fprintf(stdout, \
            "Error : {index : %lu, diff : %lu, opt : %lf, res of Hos : %lf(%016lx), res of Dev : %lf(%016lx)}\n",\
            i, diff, optBuf[i], resH, reResH, resD, reResD);
	    errNum++;
	}
    }
    if(errNum != 0){
    	fprintf(stdout, "Failed to test sin\n");
	return -1;
    }else{
    	fprintf(stdout, "PASS : sin\n");
	return 0;
    }
    
}

void testEvaluSin(size_t evaNum, int clusterId, char *program){
    hthread_dev_open(clusterId);
    hthread_dat_load(clusterId, program);
    size_t bufSize  = evaNum * sizeof(double);
    double *optBuf  = (double *)hthread_malloc(clusterId, bufSize, HT_MEM_RO);
    double *resBufD = (double *)hthread_malloc(clusterId, bufSize, HT_MEM_WO);
    double *resBufH = (double *)malloc(bufSize);
    int i;
    for(i = 0; i < evaNum; i++){
        optBuf[i] = (double)((i % 10000) - 5000);
        resBufH[i] = sin(optBuf[i]);
    }
    #if 1
    unsigned long int args[4];
    args[0] = (uint64_t)evaNum;
    args[1] = CORE_NUM;
    args[2] = (uint64_t)optBuf;
    args[3] = (uint64_t)resBufD;
    int threadId = hthread_group_create(clusterId, CORE_NUM, "kernel_evaluSin", 2, 2, args);
    #else
    unsigned long int args[3];
    args[0] = (uint64_t)evaNum;
    args[1] = (uint64_t)optBuf;
    args[2] = (uint64_t)resBufD;
    int threadId = hthread_group_create(clusterId, CORE_NUM, "kernel_evaluSinOnSingleCore", 1, 2, args);
    #endif

    hthread_group_wait(threadId);
    comBuf_f64(optBuf, resBufH, resBufD, evaNum, 2);
    hthread_dev_close(clusterId);
}

int main(int argc, char **argv){
    char *program = "helloSin.dev.dat";
    size_t dataNum = (16 * 1000 + 345 ) * 24 + 13;
    int clusterId = 0;
    if(argc > 2){
    	program = argv[1];
    }
    if(argc > 2){
    	dataNum = (size_t)atoi(argv[2]);
    }
    if(argc > 3){
    	clusterId = atoi(argv[3]);
    }
    fprintf(stdout, "dat : %s, clusterId : %d, dataNum : %lu\n", program, clusterId, dataNum);
    testEvaluSin(dataNum, clusterId, program);
    return 0;
}
