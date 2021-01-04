main: build
	#gdb --args ./write in.note out.pcm SINE
	./write harmony1.note harmony1.pcm TRIANGLE
	./write harmony2.note harmony2.pcm TRIANGLE
	./write bass.note bass.pcm SINE
	./write arp.note arp.pcm SAW
	cat arp.pcm >> fullarp.pcm
	cat arp.pcm >> fullarp.pcm
	sox -t raw -r 44.1k -b 32 -c 1 -e float harmony1.pcm harmony1.wav
	sox -t raw -r 44.1k -b 32 -c 1 -e float harmony2.pcm harmony2.wav
	sox -t raw -r 44.1k -b 32 -c 1 -e float bass.pcm bass.wav
	sox -t raw -r 44.1k -b 32 -c 1 -e float fullarp.pcm fullarp.wav
	#aplay -f float_le -r 44100 bass.pcm
	sox -m harmony1.wav harmony2.wav bass.wav fullarp.wav finished.wav
	aplay finished.wav
clean:
	rm write *.o *.pcm *.wav
build: write file_read frequency time amplitude instruments
	gcc -g -Wall -pedantic write.o file_read.o frequency.o instruments.o time.o amplitude.o -lm -o write
write: write.c
	gcc -g -Wall -pedantic -c write.c -o write.o
file_read: file_read.c
	gcc -g -Wall -pedantic -c file_read.c -o file_read.o
time: time.c
	gcc -g -Wall -pedantic -c time.c -o time.o
amplitude: amplitude.c
	gcc -g -Wall -pedantic -c amplitude.c -o amplitude.o
frequency: frequency.c
	gcc -g -Wall -pedantic -c frequency.c -o frequency.o
instruments: instruments.c
	gcc -g -Wall -pedantic -c instruments.c -o instruments.o
