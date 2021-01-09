#include "file_read.h"
#define BLOCK_SIZE 512
//TODO: make block size configurable at run time
void read_block(FILE** input_fps,float (*blocks)[BLOCK_SIZE],int block_size, int input_file_count)
{
	for (int i = 0;i<input_file_count;i++)
	{
		int values_read = 0;
		values_read = fread(blocks[i],sizeof(float),BLOCK_SIZE,input_fps[i]);
		//zero any unread floats
		for (int j=values_read;j<BLOCK_SIZE;j++)
		{
			blocks[i][j]=0;
		}
	}	
}
void average_blocks(float* average_block,float (*blocks)[BLOCK_SIZE],int block_size, int input_file_count)
{
	
	for (int i = 0;i<block_size;i++)
	{
		average_block[i]=0;
		for (int j = 0;j<input_file_count;j++)
		{
			average_block[i]+=blocks[j][i];
			average_block[i]= average_block[i]/input_file_count;
		}
	}
}
int main(int argc, char** argv)
{
	if (argc<4)
	{
		printf("argc=%d\n",argc);
		printf("USAGE: ./mono-average <first-input-file> ... <nth-input-file> <destination-file>\n");
		printf("\t*-file = any valid filename.\n");
		return EXIT_FAILURE;
	}
	FILE** input_fps = NULL; //pointers to the input files
	int* bytes_per_file = NULL; //blocks left to write in each file
	float (*block)[BLOCK_SIZE]=NULL; //memory for blocks
	FILE* destination_fp = fopen(argv[argc-1],"wb"); //file to output to
	int input_file_count = argc - 2; //count of input files
	printf("destination-file=%s\n",argv[argc-1]);

	//allocate and open each input file pointer
	input_fps = (FILE**)malloc(input_file_count*sizeof(FILE*));
	printf("input-files=");
	for (int i = 0;i<input_file_count;i++)
	{
		printf("%s ",argv[i+1]);
		input_fps[i]=fopen(argv[i+1],"rb");
	}	
	printf("\n");

	//record the number of blocks left to write per file	
	printf("bytes_per_file=");
	bytes_per_file = malloc(input_file_count*sizeof(int));
	int longest_byte_index = 0; //tells us which input file has the most bytes
	for (int i = 0;i<input_file_count;i++)
	{
		bytes_per_file[i] = file_size(input_fps[i]);
		if (bytes_per_file[i]>bytes_per_file[longest_byte_index])
		{
			longest_byte_index=i;
		}		

		printf("%d ",bytes_per_file[i]);
	}	
	printf("\n");
	printf("%s is the largest file with %d bytes.\n",argv[1+longest_byte_index],bytes_per_file[longest_byte_index]);


	//blocks of samples to write
	block=(float (*)[BLOCK_SIZE])malloc(sizeof(float[BLOCK_SIZE])*input_file_count);

	//average and write blocks
	int full_blocks_to_write = bytes_per_file[longest_byte_index]/(BLOCK_SIZE*sizeof(float));
	float average_block[BLOCK_SIZE] = {0};
	for (int i=0;i<full_blocks_to_write;i++)
	{
		read_block(input_fps,block,BLOCK_SIZE,input_file_count);
		average_blocks(average_block,block,BLOCK_SIZE,input_file_count);
		fwrite(average_block,sizeof(float),BLOCK_SIZE,destination_fp);
	}

	//handle any leftover samples not in a block
	int leftover_bytes = bytes_per_file[longest_byte_index]-full_blocks_to_write*BLOCK_SIZE*sizeof(float);
	read_block(input_fps,block,BLOCK_SIZE,input_file_count);
	average_blocks(average_block,block,BLOCK_SIZE,input_file_count);
	fwrite(average_block,1,leftover_bytes,destination_fp);

	//close file pointers
	fclose(destination_fp);
	for (int i = 0;i<input_file_count;i++)
	{
		fclose(input_fps[i]);
	}	
	
	//free memory
	free(input_fps);
	free(bytes_per_file);
	free(block);
	return EXIT_SUCCESS;
}
