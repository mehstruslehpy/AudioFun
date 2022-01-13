#ifndef MIDI_FUNCTIONS_
#define MIDI_FUNCTIONS_
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <arpa/inet.h> //REMOVE THIS ONE LATER USING ENDIANNESS HEADER STUFF
#include "midi_types.h" 
#include "rectangle_stack.h" 

void writeVarLen (uint32_t value, FILE* outfile);
uint32_t readVarLen (FILE* infile);
void readMidiFileToRectStack(FILE* infile,RectStack* stk);
void readMidiHeaderChunk(FILE* infile,MidiHeaderChunk* hdr);
void writeMidiHeaderChunk(FILE* outfile,MidiHeaderChunk* hdr);
void readMidiTrackChunk(FILE* infile,MidiTrackChunk* trk);
void readMidiTrackEvent(FILE* infile);
void readMidiFileToEnglish(FILE* infile);
#endif
