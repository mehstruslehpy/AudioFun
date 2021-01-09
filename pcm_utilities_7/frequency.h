#ifndef FREQUENCY_H 
#define FREQUENCY_H 
#include <stdlib.h>
#include <string.h>
#include <math.h>
//TODO: add extra formats
//TODO: document all formats
//TODO: clean up code so it's not just a pile of switch statements.
double read_note(char* str);
double frequency_format(char* str);
double midi_format(char* str);
double extended_midi_format(char* str);
//a more general scale format would be nice
double major_scale_format(char* str);
double minor_scale_format(char* str);
double note_format(char* str);
//utility functions
double midi_to_freq(double midinote);
double notestrs_to_freq(char* note,char* octave);
#endif
