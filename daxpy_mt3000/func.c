double 
exampleFunc(double x, double y){
	return (x + y) * (x - y);
}

static inline 
double sfma_example(double x, double y, double z){
	double ret;
	asm volatile("SFMULAD.M1 %1, %2, %3, %0\n\t"
			:"=r"(ret)
			:"r"(x), "r"(y),"r"(z));
	return ret;
}

#include <compiler/m3000.h>
static inline 
lvector double  vfma_example(lvector double x, \
		lvector double y, lvector double z){
	lvector double ret;
	asm volatile("VFMULAD.M1 %1, %2, %3, %0\n\t"
			:"=v"(ret)
			:"v"(x), "v"(y),"v"(z));
	return ret;
}
