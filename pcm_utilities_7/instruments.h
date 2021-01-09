#ifndef INSTRUMENTS_H 
#define INSTRUMENTS_H 
#include <math.h>
#include <stdlib.h>
//TODO: Add more sound generators
//TODO: Add fx library
double sine_gen(double x,double rate);
double triangle_gen(double x,double rate);
double square_gen(double x,double rate);
double saw_gen(double x,double rate);
double noise_gen(double x,double rate);
#endif
