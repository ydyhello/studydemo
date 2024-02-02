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

__global__
void daxpy_kernel(uint64_t n, double a, double *x, double *y){
    for (uint64_t i = 0; i < n; ++i){
        y[i] = a * x[i] + y[i];
    }
}
