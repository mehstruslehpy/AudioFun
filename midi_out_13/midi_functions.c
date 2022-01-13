#include "midi_functions.h"
//TODO: These are just pseudocode so far
//TODO: Implement own versions of byte order swapping stuff like htons,ntohl and junk
//TODO: Parse division in header chunk better using midi spec
void writeVarLen(uint32_t value, FILE* outfile) 
{ 
	uint32_t buffer; 
	buffer = value & 0x7f; 
	while ((value >>= 7) > 0) 
	{ 
		buffer <<= 8; 
		buffer |= 0x80; 
		buffer += (value & 0x7f); 
	} 
	while (true) 
	{ 
		putc(buffer,outfile); 
		if (buffer & 0x80) 
			buffer >>= 8; 
		else 
			break; 
	}  
} 

uint32_t readVarLen (FILE* infile) 
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
void readMidiFileToRectStack(FILE* infile,RectStack* stk)
{}
void readMidiHeaderChunk(FILE* infile,MidiHeaderChunk* hdr)
{
	hdr->type[0]=fgetc(infile);
	hdr->type[1]=fgetc(infile);
	hdr->type[2]=fgetc(infile);
	hdr->type[3]=fgetc(infile);
	fread(&hdr->length,sizeof(uint32_t),1,infile);
	hdr->length = ntohl(hdr->length);
	fread(&hdr->format,sizeof(uint16_t),1,infile);
	hdr->format = ntohs(hdr->format);
	fread(&hdr->ntrks,sizeof(uint16_t),1,infile);
	hdr->ntrks = ntohs(hdr->ntrks);
	fread(&hdr->division,sizeof(uint16_t),1,infile);
	hdr->division = ntohs(hdr->division);
}
void writeMidiHeaderChunk(FILE* outfile,MidiHeaderChunk* hdr)
{ 
		putc(hdr->type[0],outfile); 
		putc(hdr->type[1],outfile); 
		putc(hdr->type[2],outfile); 
		putc(hdr->type[3],outfile); 
		writeVarLen(hdr->length,outfile);
		uint16_t fmt = htons(hdr->format);
		uint16_t ntr = htons(hdr->ntrks);
		uint16_t div = htons(hdr->division);
		fwrite(&fmt,sizeof(uint16_t),1,outfile);
		fwrite(&ntr,sizeof(uint16_t),1,outfile);
		fwrite(&div,sizeof(uint16_t),1,outfile);
}
void readMidiTrackChunk(FILE* infile,MidiTrackChunk* trk)
{
	trk->type[0]=fgetc(infile);
	trk->type[1]=fgetc(infile);
	trk->type[2]=fgetc(infile);
	trk->type[3]=fgetc(infile);
	fread(&trk->length,sizeof(uint32_t),1,infile);
	trk->length = ntohl(trk->length);
	//DEBUG: For now just skip all the actual events and junk
	for (int i=0; i<trk->length;i++)
		getc(infile);
}

void readMidiTrackEvent(FILE* infile)
{}
void readMidiFileToEnglish(FILE* infile)
{
	//Read the header chunk
	MidiHeaderChunk hdr;
	readMidiHeaderChunk(infile,&hdr);	
	printf("Midi Header Chunk:\n");
	printf("\ttype: %c%c%c%c\n\tlength: %d\n\tformat: %d\n\tntrks: %d\n",
			hdr.type[0],hdr.type[1],hdr.type[2],hdr.type[3],
			hdr.length,
			hdr.format,
			hdr.ntrks);
	
	if (!(0x8000&hdr.division)) //if the msb is not set
		printf("\tdivision: %d ticks per quarter note\n",hdr.division);
	else
	{
		printf("\tdivision:\n");
		printf("\t\tframes per second: %d\n",(0x7F00&hdr.division)>>8); //bits 8 to 14 are frames per second
		printf("\t\tticks per frame: %d\n",0x00FF&hdr.division); //bits 0 to 7 are ticks per frame
	}
	
	//Print track/format mismatch error
	if (hdr.format==0&&hdr.ntrks!=1)
	{
		printf("ERROR: Malformed midi file, format 0 files cannot contain more than one track!\n");
		return;
	}

	//read all the track chunks
	MidiTrackChunk trk;
	for (int i=0; i<hdr.ntrks; i++)
	{
		printf("Midi Track Chunk %d:\n",i+1);
		readMidiTrackChunk(infile,&trk);
		printf("\ttype: %c%c%c%c\n\tlength: %d\n\tevents: (SKIPPED)\n",
			trk.type[0],trk.type[1],trk.type[2],trk.type[3],
			trk.length);
	
	}
}

