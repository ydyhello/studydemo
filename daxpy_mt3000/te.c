double func(double *ptr,\
     double a, double b,\
     double c, double d){
    return ((a+b)*(c+d)) \
          * ((a-b)*ptr[0]);
}

double 
complex_mul_real(double xr, double xi, 
		 double yr, double yi){
	return xr * yr - xi * yi;
}
