main: build 
	@echo "Run make test to test the system"
	@echo "Run make sample-track1 to play a sample track"
test: build
	./write beat1.note beat1.pcm NOISE
	#gdb --args ./write beat1.note beat1.pcm NOISE
	cat beat1.pcm >> tmp.pcm
	cat beat1.pcm >> tmp.pcm
	mv tmp.pcm beat1.pcm
	aplay -f float_le -r 44100 beat1.pcm 
sample-track1: build
	$(MAKE) -C ./sample-track1/
clean:
	rm -f write *.o *.pcm *.wav
	$(MAKE) -C ./sample-track1/ clean
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
