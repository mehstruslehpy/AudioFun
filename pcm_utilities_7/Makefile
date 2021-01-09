main: build 
	@echo "Run make test to test the system"
test: build
	./write ./sample-track1/arp.note arp.pcm SAW
	./write ./sample-track1/rand.note rand.pcm NOISE
	./mono-average arp.pcm rand.pcm averaged.pcm
	@echo "Playing averaged files:"
	aplay -f float_le -r 44100 averaged.pcm 
	./append averaged.pcm averaged.pcm doubled.pcm
	@echo "Playing appended file:"
	aplay -f float_le -r 44100 doubled.pcm 
clean:
	rm -f write append mono-average *.o *.pcm *.wav
build: mono-average append write file_read frequency time amplitude instruments
	gcc -g -Wall -pedantic write.o file_read.o frequency.o instruments.o time.o amplitude.o -lm -o write
	gcc -g -Wall -pedantic append.o file_read.o frequency.o instruments.o time.o amplitude.o -lm -o append
	gcc -g -Wall -pedantic mono-average.o file_read.o frequency.o instruments.o time.o amplitude.o -lm -o mono-average
#utilities
write: write.c
	gcc -g -Wall -pedantic -c write.c -o write.o
append: append.c
	gcc -g -Wall -pedantic -c append.c -o append.o
mono-average: mono-average.c
	gcc -g -Wall -pedantic -c mono-average.c -o mono-average.o
#libraries
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
