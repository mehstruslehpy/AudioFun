#include "file_read.h"
#define BLOCK_SIZE 512
//TODO: Make block size configurable at runtime
int main(int argc, char** argv)
{
	if (argc!=4)
	{
		printf("USAGE: ./append <first-file> <second-file> <destination-file>\n");
		printf("\tfirst-file = any valid filename.\n");
		printf("\tsecond-file = any valid filename.\n");
		printf("\tdestination-file = any valid filename.\n");
		return EXIT_FAILURE;
	}
	FILE* first_fp = fopen(argv[1],"rb");
	FILE* second_fp = fopen(argv[2],"rb");
	FILE* destination_fp = fopen(argv[3],"wb");
	int file1_bytes = file_size(first_fp);
	int file1_blocks = file1_bytes/(sizeof(float)*BLOCK_SIZE);
	int file2_bytes = file_size(second_fp);
	int file2_blocks = file2_bytes/(sizeof(float)*BLOCK_SIZE);

	printf("first-file=%s\n",argv[1]);
	printf("second-file=%s\n",argv[2]);
	printf("destination-file=%s\n",argv[3]);

	//block of samples to write
	float block[BLOCK_SIZE]={0};

	//write all blocks of first file
	for (int i=0;i<file1_blocks;i++)
	{
		fread(block,sizeof(float),BLOCK_SIZE,first_fp);
		fwrite(block,sizeof(float),BLOCK_SIZE,destination_fp);
	}	
	//write any leftover bytes of first file
	fread(block,sizeof(float),BLOCK_SIZE,first_fp);
	fwrite(block,1,file1_bytes-file1_blocks*BLOCK_SIZE*sizeof(float),destination_fp);

	//write all blocks of second file
	for (int i=0;i<file2_blocks;i++)
	{
		fread(block,sizeof(float),BLOCK_SIZE,second_fp);
		fwrite(block,sizeof(float),BLOCK_SIZE,destination_fp);
	}	
	//write any leftover bytes of first file
	fread(block,sizeof(float),BLOCK_SIZE,second_fp);
	fwrite(block,1,file2_bytes-file2_blocks*BLOCK_SIZE*sizeof(float),destination_fp);

	//clean up
	fclose(first_fp);
	fclose(second_fp);
	fclose(destination_fp);
	return EXIT_SUCCESS;
}
