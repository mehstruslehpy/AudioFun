#ifndef MIDI_TYPES_
#define MIDI_TYPES_
#include <stdint.h>

//See also: https://www.personal.kent.edu/~sbirch/Music_Production/MP-II/MIDI/midi_file_format.htm

typedef struct midi_event 
{
	uint8_t status_byte;
	uint8_t data_byte1;
	uint8_t data_byte2;
} MidiEvent;

typedef struct sysex_event 
{
	uint8_t leading_byte; //should be 0xF0 or 0xF7
	uint32_t length; //length of data member in bytes
	uint8_t* data;
} SysexEvent;

typedef struct MetaEvent 
{
	uint8_t leading_byte; //should always be 0xFF
	uint8_t type_byte; //always less than 128
	uint32_t length; //length of data member
	uint8_t* data;
} MetaEvent;

typedef enum { UNKNOWN, MIDI_EVENT, SYSEX_EVENT, META_EVENT } EventType;

typedef struct midi_file_event
{
	EventType type;	
	MidiEvent midi_event;	
	SysexEvent sysex_event;
	MetaEvent meta_event;
} MidiFileEvent;

typedef struct midi_track_event
{
	uint32_t delta_time;
	MidiFileEvent event; //???? One structure or three????
} MidiTrackEvent;

typedef struct midi_header_chunk 
{
	uint8_t type[4]; //always the four ascii chars 'MThd'.
	uint32_t length; //always the number 6 (high byte first).
	uint16_t format; //always 0,1 or 2 (most significant byte first).
	uint16_t ntrks; //the number of track chunks in the file, always 1 for format 0 files (MSB first).
	uint16_t division; //see spec.
} MidiHeaderChunk;

typedef struct midi_track_chunk
{
	uint8_t type[4]; //always the four ascii chars 'MTrk'.
	uint32_t length; //length in bytes of event. (I THINK)
	MidiTrackEvent* mtrk_event; //one or more midi track events.
} MidiTrackChunk;
#endif
