#include <stdio.h>
#include <stdlib.h>
#include <math.h>
const int MAX_NAME = 60;
const int SAMPLE_RATE = 44100;
int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1],"wb");
	double amplitude = atof(argv[2]);
	double freq = atof(argv[3]);
	double angleincr = 2*M_PI*freq/SAMPLE_RATE;
	double phase = atof(argv[4]);
	int duration = atoi(argv[5]);
	for (int i=0;i<duration;i++)
	{
		float value = amplitude*sin(angleincr*i+phase);
		fwrite(&value,sizeof(float),1,fp);
	}
	return EXIT_SUCCESS;
}
