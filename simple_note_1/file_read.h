#ifndef FILE_READ_H
#define FILE_READ_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
//libraries for decoding noteline values
#include "types.h"
#include "amplitude.h"
#include "time.h"
#include "frequency.h"
#define NDEBUG
//TODO: Add commenting and whitespace skipping functionality
void print_noteline(char* start_msg,Noteline* n,char* end_msg);
//count lines in file
int lines_per_file(FILE* fp);
//read format info
Format read_format(FILE* fp);
//read a single note
Noteline read_noteline(FILE* fp,Format fmt);
int is_comment(char* str);
int is_empty(char* str);
#endif
