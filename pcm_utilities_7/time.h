#ifndef TIME_H 
#define TIME_H 
#include <stdlib.h>
#include <string.h>
#include "types.h"
//TODO: Add more time formats
//TODO: Document all time formats
double read_time(char* str,Format fmt);
double second_format(char* str,int sample_rate);
double beats_format(char* str,int sample_rate);
double extended_time_format(char* str,int sample_rate);
#endif
