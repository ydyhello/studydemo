#include <stdint.h>
#include <compiler/m3000.h>
#include "hthread_device.h"

void someKernel_vector(uint64_t width, uint64_t height, \
                  lvector double  *x, lvector double  *y);
//
void someKernel_threads(uint64_t width, uint64_t height, \
                                    double *x, double *y){
    //16 ~ 25 chunk
    uint64_t width_c  = width  / 4;
    uint64_t height_c = height / 4;
    uint64_t chunkEles = width_c * height_c;
    uint64_t chunkSize = chunkEles *sizeof(double);
    lvector double  *x_am = vector_malloc(chunkSize);
    lvector double  *y_am = vector_malloc(chunkSize);
    //
    uint64_t w = 0, h = 0;
    for(h = 0; h < height; h += height_c){
      for(w = 0; w < width; w += width_c){
        uint64_t aWidth  = (width  - w) > width_c  ? width_c  : (width  - w);
        uint64_t aHeight = (height - w) > height_c ? height_c : (height - w);
        uint64_t offset  = h * width + w;
        uint64_t src_row_num  = aHeight;
        uint64_t src_row_size = aWidth * sizeof(double);
        uint64_t src_row_step = (width - aWidth) * sizeof(double);
        uint64_t dst_row_num  = src_row_num;
        uint64_t dst_row_size = src_row_size;
        uint64_t dst_row_step = 0;
        unsigned int  x_lp = dma_p2p(x + offset, src_row_num, src_row_size, src_row_step, \
                                   x_am, dst_row_num, dst_row_size, dst_row_step, false, 0);
        unsigned int  y_lp = dma_p2p(y + offset, src_row_num, src_row_size, src_row_step, \
                                   y_am, dst_row_num, dst_row_size, dst_row_step, false, 0);
        dma_wait(x_lp);dma_wait(y_lp);
        someKernel_vector(aWidth, aHeight, x_am, y_am);
      }
    }
    vector_free(x_am);
    vector_free(y_am);
}
