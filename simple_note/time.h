#ifndef TIME_H 
#define TIME_H 
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#define NDEBUG
double read_time(char* str,Format fmt);
double second_format(char* str,int sample_rate);
double beats_format(char* str,int sample_rate);
double extended_time_format(char* str,int sample_rate);
#endif
