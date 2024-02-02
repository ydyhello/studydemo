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





////////////////////////////////////////////////////////////////////////////////
// Process an array of optN options on CPU
////////////////////////////////////////////////////////////////////////////////
extern "C" void BlackScholesCPU(
    float *h_Call, //Call option price
    float *h_Put,  //Put option price
    float *h_S,    //Current stock price
    float *h_X,    //Option strike price
    float *h_T,    //Option years
    float R,       //Riskless rate of return
    float V,       //Stock volatility
    unsigned int optionCount
);


////////////////////////////////////////////////////////////////////////////////
// Process an array of optN options on CPU
////////////////////////////////////////////////////////////////////////////////
extern "C" void BlackScholesCPU_VecOpt(
    float *h_Call, //Call option price
    float *h_Put,  //Put option price
    float *h_S,    //Current stock price
    float *h_X,    //Option strike price
    float *h_T,    //Option years
    float R,       //Riskless rate of return
    float V,       //Stock volatility
    unsigned int optionCount
);

extern "C"
int Compare_Result(size_t optionCount, float *Call_v, float *Put_v, float *Call_s, float *Put_s);

////////////////////////////////////////////////////////////////////////////////
// OpenCL Black-Scholes kernel launcher
////////////////////////////////////////////////////////////////////////////////

extern "C" void closeBlackScholes(void);
