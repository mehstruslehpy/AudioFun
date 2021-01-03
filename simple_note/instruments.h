#ifndef INSTRUMENTS_H 
#define INSTRUMENTS_H 
#include <assert.h>
#include <math.h>
#define NDEBUG
double sine_gen(double x,double rate);
double triangle_gen(double x,double rate);
double square_gen(double x,double rate);
double saw_gen(double x,double rate);
#endif
