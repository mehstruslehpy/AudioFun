#include "time.h"
#define BUF_LEN 2048
double read_time(char* str,Format fmt)
{
	assert(str!=NULL);
	switch (str[0])
	{
		case 's': //seconds format is s followed by a number of seconds
		case 'S':
			str++;
			return second_format(str,fmt.sample_rate);
		case 'b': //beats format is b followed by a bpm and number of beats 
		case 'B': //an underscore separates the bpm and number of beats
			str++;
			return beats_format(str,fmt.sample_rate);
		case 'e': //extended beats format is an e followed by a bpm
		case 'E': //followed by a number of beats followed by a fractional subdivision of the beat
			str++;
			return extended_time_format(str,fmt.sample_rate);
		default:
			return atof(str);
	}
}
double second_format(char* str,int sample_rate)
{
	return atof(str)*(double)sample_rate;
}
double beats_format(char* str,int sample_rate)
{
	char* bpm = strtok(str,"_");
	char* beats = strtok(NULL,"_");
	return atof(beats)*(60/atof(bpm))*(sample_rate);
}
double extended_time_format(char* str,int sample_rate)
{
	//printf("DEBUG: str=%s\n",str);
	char* bpm = strtok(str,"_");
	//printf("DEBUG: bpm=%s\n",bpm);
	char* beats = strtok(NULL,"_");
	//printf("DEBUG: beats=%s\n",beats);
	char* fraction = strtok(NULL,"_");
	//printf("DEBUG: fraction=%s\n",fraction);
	char* numerator = strtok(fraction,"/");
	//printf("DEBUG: numerator=%s\n",numerator);
	char* denominator = strtok(NULL,"/");
	//printf("DEBUG: denominator=%s\n\n",denominator);
	return (atof(beats)+atof(numerator)/atof(denominator))*(60/atof(bpm))*(sample_rate);
}
