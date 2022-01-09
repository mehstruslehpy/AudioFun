#include <gtk/gtk.h>
#include <cairo.h>
#include "rectangle_stack.h"
#include "endian.h"

int main (int argc, char * argv[]) 
{
	//run some tests
	printf("Hello world!\n");
	printf("Endianness: %s.\n",bigEndian()?"big-endian":"little-endian");
	//for (uint16_t i=0;i<65535;i++)
	for (uint16_t i=0;i<8;i++)
		printf("machine endianness of uint16_t %d in hex: %04X swapped: %04X.\n",i,i,swap_uint16(i));
	//for (uint32_t i=0;i<65535;i++)
	for (uint32_t i=0;i<8;i++)
		printf("machine endianness of unit32_t %d in hex: %08X swapped: %08X.\n",i,i,swap_uint32(i));
	
	return 0;
}

