#include <stdint.h>
#include <math.h>
#include "hthread_device.h"
#include <compiler/m3000.h>
#define MaxVectorCount 100
///////////////////////////////////////////////////////////////////////////////
// Rational approximation of cumulative normal distribution function
///////////////////////////////////////////////////////////////////////////////
static double CND(double d, unsigned int i){
    const double       A1 = 0.31938153;
    const double       A2 = -0.356563782;
    const double       A3 = 1.781477937;
    const double       A4 = -1.821255978;
    const double       A5 = 1.330274429;
    const double RSQRT2PI = 0.39894228040143267793994605993438;

    double
        K = 1.0 / (1.0 + 0.2316419 * fabs(d));

    double
        cnd = RSQRT2PI * exp(- 0.5 * d * d) * 
        (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));

    if(d > 0)
        cnd = 1.0 - cnd;

    return cnd;
}

///////////////////////////////////////////////////////////////////////////////
// Black-Scholes formula for both call and put
///////////////////////////////////////////////////////////////////////////////
static void BlackScholesBodyCPU(
    float* call, //Call option price
    float* put,  //Put option price
    float Sf,    //Current stock price
    float Xf,    //Option strike price
    float Tf,    //Option years
    float Rf,    //Riskless rate of return
    float Vf,     //Stock volatility
    unsigned int i
){
    double S = Sf, X = Xf, T = Tf, R = Rf, V = Vf;

    double sqrtT = sqrt(T);
    double    d1 = (log(S / X) + (R + 0.5 * V * V) * T) / (V * sqrtT);
    double    d2 = d1 - V * sqrtT;
    double CNDD1 = CND(d1, i);
    double CNDD2 = CND(d2, i);

    //Calculate Call and Put simultaneously
    double expRT = exp(- R * T);
    *call = (float)(S * CNDD1 - X * expRT * CNDD2);
    *put  = (float)(X * expRT * (1.0 - CNDD2) - S * (1.0 - CNDD1));
}

__global__
void BlackScholesKernel(uint64_t optionCount, \
                                    float  R, \
                                    float  V, \
                               float *d_Call, \
                                float *d_Put, \
                                  float *d_S, \
                                  float *d_X, \
                                   float *d_T){
    //
    for(unsigned int i = 0; i < optionCount; i++){
        BlackScholesBodyCPU(
            &d_Call[i],
            &d_Put[i],
            d_S[i],
            d_X[i],
            d_T[i],
            R,
            V,
            i
        );
    }   
}

__global__
void BlackScholesthreads(uint64_t optionCount, \
                                    float  R, \
                                    float  V, \
                               float *d_Call, \
                                float *d_Put, \
                                  float *d_S, \
                                  float *d_X, \
                                   float *d_T){
    int threadId = get_thread_id();
    int threadsNum = get_group_size();
    uint64_t optionCount_p = optionCount/threadsNum;
    uint64_t extras = optionCount%threadsNum;
    uint64_t offset;
    if(threadId < extras){
        optionCount_p++;
        offset=threadId*optionCount_p;
    }else{
        offset=threadId*(optionCount_p+1)-(threadId-extras);
    }
    // BlackScholes(
    BlackScholesKernel(
            optionCount_p,
            R,
            V,
            d_Call+offset,
            d_Put+offset,
            d_S+offset,
            d_X+offset,
            d_T+offset
    );
}

__global__
void BlackScholes(uint64_t optionCount, \
                                    float  R, \
                                    float  V, \
                               float *d_Call, \
                                float *d_Put, \
                                  float *d_S, \
                                  float *d_X, \
                                   float *d_T){
    size_t cacheLen = MaxVectorCount * 16;
    size_t cacheSize = cacheLen * sizeof(float);
    lvector float *d_Call_Cache = (lvector float *)vector_malloc(cacheSize);
    lvector float *d_Put_Cache = (lvector float *)vector_malloc(cacheSize);
    lvector float *d_S_Cache = (lvector float *)vector_malloc(cacheSize);
    lvector float *d_X_Cache = (lvector float *)vector_malloc(cacheSize);
    lvector float *d_T_Cache = (lvector float *)vector_malloc(cacheSize);
    
    

    size_t tmpLen, tmpSize;
    for(unsigned int i = 0; i < optionCount; i += tmpLen){
        tmpLen = (optionCount - i) > cacheLen ? cacheLen : (optionCount - i);
        tmpSize = tmpLen * sizeof(float);
        
        // vector_load(&d_Call[i], d_Call_Cache, tmpSize);
        // vector_load(&d_Put[i], d_Put_Cache, tmpSize);
        vector_load(&d_S[i], d_S_Cache, tmpSize);
        vector_load(&d_X[i], d_X_Cache, tmpSize);
        vector_load(&d_T[i], d_T_Cache, tmpSize);
        lvector double R_vec = vec_svbcast((double)R);	
        lvector double V_vec = vec_svbcast((double)V);
        lvector float R_vecf=(lvector float)R_vec;
        lvector float V_vecf=(lvector float)V_vec;
        BlackScholesAM(cacheLen/16, R_vecf, V_vecf, d_Call_Cache, d_Put_Cache, d_S_Cache, d_X_Cache, d_T_Cache);
        vector_store(d_Put_Cache,&d_Put[i],tmpSize);
        vector_store(d_Call_Cache,&d_Call[i],tmpSize);

    }
    vector_free(d_Call_Cache);
    vector_free(d_Put_Cache);
    vector_free(d_S_Cache);
    vector_free(d_X_Cache);
    vector_free(d_T_Cache);
}   

__global__
void BlackScholesAM(uint64_t optionCount, \
                                lvector float  R, \
                                lvector float  V, \
                                lvector float *d_Call, \
                                lvector float *d_Put, \
                                lvector float *d_S, \
                                lvector float *d_X, \
                                lvector float *d_T){
    //
    lvector double k=vec_svbcast(0.5);
    lvector float K=(lvector float)k;
    lvector double a1=vec_svbcast(0.2316419);
    lvector float A1=(lvector float)a1;
    lvector double a2=vec_svbcast(-0.5);
    lvector float A2=(lvector float)a2;
    lvector double rsqrt2pi = vec_svbcast(0.39894228040143267793994605993438);
    lvector float RSQRT2PI=(lvector float)rsqrt2pi;

    lvector double b5=vec_svbcast(1.330274429);
    lvector float B5=(lvector float)b5;
    lvector double b4=vec_svbcast(-1.821255978);
    lvector float B4=(lvector float)b4;
    lvector double b3=vec_svbcast(1.781477937);
    lvector float B3=(lvector float)b3;
    lvector double b2=vec_svbcast(-0.356563782);
    lvector float B2=(lvector float)b2;
    lvector double b1=vec_svbcast(0.31938153);
    lvector float B1=(lvector float)b1;

    lvector double one=vec_svbcast(1.0);
    lvector float ONE=(lvector float)one;

    

    for(unsigned int i = 0; i < optionCount; i++){
        lvector float sqrtT = vm_sqrtf32(d_T[i]);

        //float d1 = (log(d_S[i] / d_X[i]) + (R + 0.5 * V * V) * d_T[i]) / (V * sqrtT);
        lvector float d1 = vm_logf32_u10(vm_fdivf32(d_S[i],d_X[i]));
        lvector float d2 = vec_muli(V,V);
        lvector float d3 = vec_muli(K,d2);
        lvector float d4 = vec_muli(d3,d_T[i]);
        lvector float d5 = d1 + d4;
        lvector float d6 = vec_muli(V, sqrtT);
        lvector float d7 = vm_fdivf32(d5, d6); // d1

        lvector float d8 = d7 - vec_muli(V,sqrtT); // d2
        lvector float CNDD11 = vm_fdivf32(1.0 , (1.0 + vec_muli(A1 , vec_abs(d7)))); // K
        //     cnd = RSQRT2PI * exp(- 0.5 * d * d) * 
        //     (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));
        lvector float CNDD12 = vec_muli(d7,d7);
        lvector float CNDD13 = vec_muli(A2,CNDD12);
        lvector float CNDD14 = vm_frfrexpf32(CNDD13);
        lvector float CNDD15 = vec_muli(RSQRT2PI,CNDD14);
        lvector float CNDD16 = vec_mula(CNDD11, B5, B4);
        lvector float CNDD17 = vec_mula(CNDD11, CNDD16, B3);
        lvector float CNDD18 = vec_mula(CNDD11, CNDD17, B2);
        lvector float CNDD19 = vec_mula(CNDD11, CNDD18, B1);
        lvector float CNDD110 = vec_muli(CNDD11, CNDD19); 
        lvector float cnd1 = vec_muli(CNDD15,CNDD110);

        lvector float CNDD22 = vec_muli(d8,d8);
        lvector float CNDD23 = vec_muli(A2,CNDD22);
        lvector float CNDD24 = vm_frfrexpf32(CNDD23);
        lvector float CNDD25 = vec_muli(RSQRT2PI,CNDD24);
        lvector float CNDD26 = vec_mula(CNDD11, B5, B4);
        lvector float CNDD27 = vec_mula(CNDD11, CNDD26, B3);
        lvector float CNDD28 = vec_mula(CNDD11, CNDD27, B2);
        lvector float CNDD29 = vec_mula(CNDD11, CNDD28, B1);
        lvector float CNDD210 = vec_muli(CNDD11, CNDD29); 
        lvector float cnd2 = vec_muli(CNDD25,CNDD210);
    
        // exp(- R * T);
        lvector float expRT = - vm_frfrexpf32(R, d_T[i]);
        // *call = (float)(S * CNDD1 - X * expRT * CNDD2);
        d_Call[i]=vec_muli(d_S[i], cnd1) -vec_muli(d_X[i],vec_muli(expRT,cnd2));
        // *put  = (float)(X * expRT * (1.0 - CNDD2) - S * (1.0 - CNDD1));
        d_Put[i]=vec_muli(d_X[i], vec_muli(expRT,(ONE - cnd2)))-vec_muli(d_S[i],(ONE-cnd1));
    }

}

