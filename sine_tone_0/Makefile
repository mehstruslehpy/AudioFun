main: build
	./write out1.pcm 1 55 0 30000
	./write out2.pcm 1 110 0 30000
	./write out3.pcm 1 220 0 30000
	./write out4.pcm 1 440 0 30000
	./write out5.pcm 1 880 0 30000
	./write out6.pcm 1 1760 0 30000
	./write out7.pcm 1 3520 0 30000
	./write out8.pcm 1 7040 0 30000
	cat out1.pcm out2.pcm out3.pcm out4.pcm out5.pcm out6.pcm out7.pcm out8.pcm > big.pcm
	aplay -f float_le -r 44100 big.pcm
clean:
	rm write *.o *.pcm
build: write.c
	gcc -g -Wall -pedantic -c write.c -o write.o
	gcc -g -Wall -pedantic write.o -lm -o write
