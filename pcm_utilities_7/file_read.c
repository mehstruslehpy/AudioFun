#include "file_read.h"
#define BUF_LEN 2048
//return file size in bytes
//this can be updated to a long int if necessary
int file_size(FILE* fp)
{
	//long int size = 0;
	int size = 0;
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	fseek(fp,0,SEEK_SET);
	return size;
}
//checks if string is a comment
int is_comment(char* str)
{
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
	int count=0;
	char file_buf[BUF_LEN]={0};
	while (fgets(file_buf,BUF_LEN,fp))
	{
		count++;
	}
	rewind(fp);
	return count;
}
int blank_lines_per_file(FILE* fp)
{
	int count=0;
	char file_buf[BUF_LEN]={0};
	while (fgets(file_buf,BUF_LEN,fp))
	{
		if(is_empty(file_buf))
		{
			count++;
		}
	}
	rewind(fp);
	return count;
}
int comments_per_file(FILE* fp)
{
	int count=0;
	char file_buf[BUF_LEN]={0};
	while (fgets(file_buf,BUF_LEN,fp))
	{
		if(is_comment(file_buf))
		{
			count++;
		}
	}
	rewind(fp);
	return count;
}
Format read_format(FILE* fp)
{
	char file_buf[BUF_LEN]={0};
	//read line into buffer for tokenizing
	fgets(file_buf,BUF_LEN,fp);
	//re-read line if comment or empty line is found
	while (is_comment(file_buf)||is_empty(file_buf))
	{
		fgets(file_buf,BUF_LEN,fp);
	}
	char* header = strtok(file_buf," ");
	//return negative -1 sample rate on error
	if (strcmp(header,"SAMPLE_RATE:")!=0) 
	{
		return (Format) {.sample_rate=-1};
	}
	//return the input sample rate on success
	char* value = strtok(NULL," ");
	return (Format) {.sample_rate=atoi(value)};
}
Noteline read_noteline(FILE* fp,Format fmt)
{
	//read line into buffer
	char file_buf[BUF_LEN]={'\0'};
	fgets(file_buf,BUF_LEN,fp);
	//re-read line if comment or empty line is found
	while (is_comment(file_buf)||is_empty(file_buf))
	{
		fgets(file_buf,BUF_LEN,fp);
	}
	//split line into components
	char* amp_str = strtok(file_buf, " ");
	char* freq_str = strtok(NULL, " ");
	char* start_str = strtok(NULL, " ");
	char* dur_str = strtok(NULL, " ");
	//translate all components to correct values
	double amp = read_amp(amp_str);
	double freq = read_note(freq_str);
	double start = read_time(start_str,fmt);
	double dur = read_time(dur_str,fmt);
	//return values
	return (Noteline) {.freq=freq,.amp=amp,.start=start,.dur=dur};
}
