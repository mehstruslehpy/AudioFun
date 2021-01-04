#include "frequency.h"
double midi_to_freq(double midinote)
{
	double c5 = 220;
	double c0 = c5*pow(0.5,5);
	double semitone_ratio = pow(2,1.0/12.0);
	return c0*pow(semitone_ratio,midinote);
}
//could use range checking
double notestrs_to_freq(char* note, char* octave)
{
	double semitone_ratio = pow(2,1.0/12.0);
	double freq = 0;
	
	//calculate base note frequency
	//could be reduced to enum or table lookup probably
	switch (note[0])
	{
		case 'a': //A0 is midinote 33
		case 'A':
			freq = midi_to_freq(33);
			break;		
		case 'b': //B0 is midinote 35
		case 'B':
			freq = midi_to_freq(35);
			break;		
		case 'c': //C0 is midinote 24
		case 'C':
			freq = midi_to_freq(24);
			break;		
		case 'd': //D0 is midinote 26
		case 'D':
			freq = midi_to_freq(26);
			break;		
		case 'e': //E0 is midinote 28
		case 'E':
			freq = midi_to_freq(28);
			break;		
		case 'f': //F0 is midinote 29
		case 'F':
			freq = midi_to_freq(29);
			break;		
		case 'g': //G0 is midinote 31
		case 'G':
			freq = midi_to_freq(31);
			break;		
		default:
			freq = midi_to_freq(24);
	}

	//calculate sharps/flats ignore naturals
	switch (note[1])
	{
		case 's':
		case 'S':
			freq = freq*semitone_ratio;
			break;
		case 'f':
		case 'F':
			freq = freq/semitone_ratio;
	}
	return freq*pow(2,atof(octave));
}
double read_note(char* str)
{
	assert(str!=NULL);
	switch (str[0])//all formats are underscore separated values
	{
		case 'f': //frequency format is f followed by a frequency
		case 'F': //it is essentially the same as the default with no f prefix
			str++;
			return frequency_format(str);
		case 'm': //midi format is m followed by a midi note
		case 'M':
			str++;
			return midi_format(str);
		case 'e': //extended midi format is e followed by a midi note
		case 'E': //and a signed pitch deviation
			str++;
			return extended_midi_format(str);
		case 'n': //note format is an n followed by a  traditional alpha numeric note
		case 'N': //with a mandatory sharp/flat/natural denoted (s/f/n) followed by an octave number
			str++;
			return note_format(str);
		case 's': //The major scale format is an s followed by an alphanumeric note (see note_format()) followed by 
		case 'S': //an octave followed by a major scale offset [0-6]
			str++;
			return major_scale_format(str);
		case 't': //The minor scale format is an t followed by an alphanumeric note (see note_format()) followed by 
		case 'T': //an octave followed by a major scale offset [0-6]
			str++;
			return minor_scale_format(str);
/*
		case 'e': //The experimental format is an e followed by a frequency
		case 'e': //a number of notes per octave followed by a note followed by an octave
			str++;
			return extended_scale_format(str);
*/
/*
		case 'i': //The interval format is an i followed by a note followed by
		case 'I': //an interval
			str++;
			return note_format(str);
*/
		default:
			return atof(str);
	}
}
double frequency_format(char* str)
{
	return atof(str);
}
double midi_format(char* str)
{
	return midi_to_freq(atof(str));
}
double extended_midi_format(char* str)
{
	char* midinote_s = strtok(str,"_");
	char* deviation_s = strtok(NULL,"_");

	double midinote = atof(midinote_s);
	double deviation = atof(deviation_s);
	
	return midi_to_freq(midinote+deviation);
}
double note_format(char* str)
{
	char* note = strtok(str,"_");
	char* octave = strtok(NULL,"_");
	return notestrs_to_freq(note,octave);
}
double major_scale_format(char* str)
{
	char* key = strtok(str,"_");
	char* octave = strtok(NULL,"_");
	char* offset = strtok(NULL,"_");
	double keyfreq = notestrs_to_freq(key,octave);
	double semitone_ratio = pow(2,1.0/12.0);

	switch (offset[0])
	{
		case '1':
			return keyfreq*pow(semitone_ratio,2);
		case '2':
			return keyfreq*pow(semitone_ratio,4);
		case '3':
			return keyfreq*pow(semitone_ratio,5);
		case '4':
			return keyfreq*pow(semitone_ratio,7);
		case '5':
			return keyfreq*pow(semitone_ratio,9);
		case '6':
			return keyfreq*pow(semitone_ratio,11);
		case '0':
		default:
			return keyfreq;
	}
}
double minor_scale_format(char* str)
{
	char* key = strtok(str,"_");
	char* octave = strtok(NULL,"_");
	char* offset = strtok(NULL,"_");
	double keyfreq = notestrs_to_freq(key,octave);
	double semitone_ratio = pow(2,1.0/12.0);

	switch (offset[0])
	{
		case '1':
			return keyfreq*pow(semitone_ratio,2);
		case '2':
			return keyfreq*pow(semitone_ratio,3);
		case '3':
			return keyfreq*pow(semitone_ratio,5);
		case '4':
			return keyfreq*pow(semitone_ratio,7);
		case '5':
			return keyfreq*pow(semitone_ratio,8);
		case '6':
			return keyfreq*pow(semitone_ratio,10);
		case '7':
			return keyfreq*pow(semitone_ratio,12);
		case '0':
		default:
			return keyfreq;
	}
}
