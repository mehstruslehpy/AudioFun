#ifndef TYPES_H
#define TYPES_H

typedef struct Format
{
	int sample_rate;
} Format;

typedef struct Noteline
{
	double amp;
	double freq;
	double start;
	double dur;
} Noteline;
#endif
