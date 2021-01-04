#include "instruments.h"
//this is an example of how the instrument generators should work
double sine_gen(double x,double rate)
{
	return sin(2*M_PI*x/rate);
}
double triangle_gen(double x,double rate)
{
	x=x/rate;
	while (x>1) x=x-1;
	while (x<0) x=x+1;
	if (x<0.5) return 4.0*x-1.0;
	else return 3.0-4.0*x;
}
double square_gen(double x,double rate)
{
	x=x/rate;
	while (x>1) x=x-1;
	while (x<0) x=x+1;
	if (x<0.5) return 1;
	else return -1;
}
double saw_gen(double x,double rate)
{
	x=x/rate;
	while (x>1) x=x-1;
	while (x<0) x=x+1;
	return 2*x-1;
}
