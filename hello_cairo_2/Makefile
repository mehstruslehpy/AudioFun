main: build
	./cairo-hello
clean:
	rm cairo-hello *.o *.png
build: cairo-hello
	gcc -g -Wall -pedantic cairo-hello.o -lcairo -o cairo-hello
cairo-hello: cairo-hello.c
	gcc -g -Wall -pedantic -I /usr/include/cairo -c cairo-hello.c -o cairo-hello.o
