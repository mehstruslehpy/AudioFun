#include "midi_functions.h" 
//TODO: These are just pseudocode so far
WriteVarLen (uint32_t value, FILE* outfile) 
{ 
	uint32_t buffer; 
	buffer = value & 0x7f; 
	while ((value >>= 7) > 0) 
	{ 
		buffer <<= 8; 
		buffer |= 0x80; 
		buffer += (value & 0x7f); 
	} 
	while (TRUE) 
	{ 
		putc(buffer,outfile); 
		if (buffer & 0x80) 
			buffer >>= 8; 
		else 
			break; 
	}  
} 

uint32_t ReadVarLen (FILE* infile) 
{ 
	uint32_t value; 
	uint8_t c; 
	if ((value = getc(infile)) & 0x80) 
	{ 
		value &= 0x7f; 
		do 
		{ 
			value = (value << 7) + ((c = getc(infile)) & 0x7f); 
		} while (c & 0x80); 
	} 
	return (value); 
}
