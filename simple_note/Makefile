main: build
	#gdb --args ./write in.note out.pcm
	./write in.note out.pcm TRIANGLE
	aplay -f float_le -r 44100 out.pcm

clean:
	rm write *.o *.pcm
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
