#include <math.h>
#include "file_read.h"
#include "instruments.h"
//TODO: Block based io will probably be faster rather than one write per sample
//TODO: Add stereo/mono modes
//TODO: Add ADSR using breakpoint files
//TODO: Add some basic block/clip programs average two files, pad a file/change file length etc.
//TODO: Add error handling
int main(int argc, char** argv)
{
	FILE* in_fp = fopen(argv[1],"r");
	int lines = lines_per_file(in_fp);
	FILE* out_fp = fopen(argv[2],"wb");
	double (*instr_ptr)(double,double) = NULL;
	if (strcmp(argv[3],"SAW")==0) instr_ptr=&saw_gen;
	else if (strcmp(argv[3],"SQUARE")==0) instr_ptr=&square_gen;
	else if (strcmp(argv[3],"TRIANGLE")==0) instr_ptr=&triangle_gen;
	else if (strcmp(argv[3],"SINE")==0) instr_ptr=&sine_gen;
	else if (strcmp(argv[3],"NOISE")==0)
	{
		srand(time(NULL));
		instr_ptr=&noise_gen;
	}
	else instr_ptr=&sine_gen;

	printf("instrument=%s\n",argv[3]);
	printf("infile=%s\n",argv[1]);
	printf("outfile=%s\n",argv[2]);

	//read sample rate
	Format fmt = read_format(in_fp);
	printf("infile-lines=%d\n",lines);
	printf("SAMPLE_RATE=%d\n",fmt.sample_rate);

	float value = 0;
	for (int i=0,tick=0;i<lines-1;i++)
	{
		//read a note from the file
		Noteline cur_note=read_noteline(in_fp,fmt);
		//double angle=2*M_PI*cur_note.freq/fmt.sample_rate;
		double angle=cur_note.freq;
		double amp=cur_note.amp;
		double start=cur_note.start;
		double dur=cur_note.dur;
		//print_noteline("cur_note=",&cur_note,"\n");

		//check values with assert
		//assert(tick<=(int)start);

		//write 0's for ticks that don't have notes
		while (tick < (int)start) 
		{
			value = 0;
			fwrite(&value,sizeof(float),1,out_fp);
			tick++;
		}

		//write actual samples for ticks that do have notes
		while (tick<start+dur)
		{
			value = amp*(*instr_ptr)(angle*tick,fmt.sample_rate);
			fwrite(&value,sizeof(float),1,out_fp);
			tick++;
		}
	}
	fclose(out_fp);
	fclose(in_fp);
	return EXIT_SUCCESS;
}
