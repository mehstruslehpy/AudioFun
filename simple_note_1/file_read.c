#include "file_read.h"
#define BUF_LEN 2048
//checks if string is a comment
int is_comment(char* str)
{
	printf("checking str=%s\n",str);
	if (str[0]=='#') return 1;
	else return 0;
}
//checks if string is all whitespace or empty
int is_empty(char *s) {
  while (*s != '\0') {
    if (!isspace((unsigned char)*s))
      return 0;
    s++;
  }
  return 1;
}
void print_noteline(char* start_msg, Noteline* n, char* end_msg)
{
	printf("%s{.amp=%f, .freq=%f, .start=%f, .dur=%f}%s",
			start_msg,
			n->amp,
			n->freq,
			n->start,
			n->dur,
			end_msg);
}
int lines_per_file(FILE* fp)
{
	assert(fp!=NULL);
	int count=0;
	char c = fgetc(fp);
	while (c!=EOF)
	{
		if (c=='\n')
		{
			count++;
		}
		c = fgetc(fp);
	}
	rewind(fp);
	return count;
}
Format read_format(FILE* fp)
{
	assert(fp!=NULL);
	char file_buf[BUF_LEN]={0};

	//read line into buffer for tokenizing
	fgets(file_buf,BUF_LEN,fp);
	char* header = strtok(file_buf," ");

	//assert header is correct
	assert(strncmp(header,"SAMPLE_RATE:",BUF_LEN)==0);
	//if header is wrong return -1 sample rate
	/*
	if (strncmp(header,"SAMPLE_RATE:",BUF_LEN)!=0)
		return (Format) {.sample_rate=-1};
	*/

	char* value = strtok(NULL," ");
	return (Format) {.sample_rate=atoi(value)};
}
Noteline read_noteline(FILE* fp,Format fmt)
{
	assert(fp!=NULL);

	//read line
	char file_buf[BUF_LEN]={'\0'};
	fgets(file_buf,BUF_LEN,fp);

	char* amp_str = strtok(file_buf, " ");
	char* freq_str = strtok(NULL, " ");
	char* start_str = strtok(NULL, " ");
	char* dur_str = strtok(NULL, " ");

	double amp = read_amp(amp_str);
	double freq = read_note(freq_str);
	double start = read_time(start_str,fmt);
	double dur = read_time(dur_str,fmt);
	
	return (Noteline) {.freq=freq,.amp=amp,.start=start,.dur=dur};
}
