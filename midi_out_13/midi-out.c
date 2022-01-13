#include <gtk/gtk.h>
#include <cairo.h>
#include "rectangle_stack.h"
#include "endian.h"
#include "midi_types.h"
#include "midi_functions.h"

int main (int argc, char * argv[]) 
{
	if (argc!=2)
	{
		printf("Supply an input file argument.\n");
		return 0;
	}

	/*
	// LOW LEVEL TESTS
	printf("Hello world!\n");
	printf("Endianness: %s.\n",bigEndian()?"big-endian":"little-endian");
	//for (uint16_t i=0;i<65535;i++)
	for (uint16_t i=0;i<8;i++)
		printf("machine endianness of uint16_t %d in hex: %04X swapped: %04X.\n",i,i,swap_uint16(i));
	//for (uint32_t i=0;i<65535;i++)
	for (uint32_t i=0;i<8;i++)
		printf("machine endianness of unit32_t %d in hex: %08X swapped: %08X.\n",i,i,swap_uint32(i));
	*/
	// TEST READING
	FILE* ifile = fopen(argv[1],"r");
	readMidiFileToEnglish(ifile);
	close(ifile);

	// TEST WRITING
	/*MidiHeaderChunk hdr =
	{
		.type="MTHd",
		.length=6,
		.format=0,
		.ntrks=1,
		.division=5,
	};*/
	//FILE* ofile = fopen("out.file","w+");
	//writeMidiHeaderChunk(ofile,&hdr);
	//readMidiHeaderChunk(ifile,&hdr);
	//printf("");
	//fclose(ofile);
	
	return 0;
}

