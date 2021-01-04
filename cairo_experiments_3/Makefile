main: build
	./cairo-hello
	./stroke
	./fill
	./showtext
	./paint
	./mask
clean:
	rm mask cairo-hello stroke fill showtext paint *.o *.png
build: cairo-hello stroke fill showtext paint mask
	gcc -g -Wall -pedantic cairo-hello.o -lcairo -o cairo-hello
	gcc -g -Wall -pedantic stroke.o -lcairo -o stroke
	gcc -g -Wall -pedantic fill.o -lcairo -o fill
	gcc -g -Wall -pedantic showtext.o -lcairo -o showtext
	gcc -g -Wall -pedantic paint.o -lcairo -o paint
	gcc -g -Wall -pedantic mask.o -lcairo -o mask
cairo-hello: cairo-hello.c
	gcc -g -Wall -pedantic -I /usr/include/cairo -c cairo-hello.c -o cairo-hello.o
stroke: stroke.c
	gcc -g -Wall -pedantic -I /usr/include/cairo -c stroke.c -o stroke.o
fill: fill.c
	gcc -g -Wall -pedantic -I /usr/include/cairo -c fill.c -o fill.o
showtext: showtext.c
	gcc -g -Wall -pedantic -I /usr/include/cairo -c showtext.c -o showtext.o
paint: paint.c
	gcc -g -Wall -pedantic -I /usr/include/cairo -c paint.c -o paint.o
mask: mask.c
	gcc -g -Wall -pedantic -I /usr/include/cairo -c mask.c -o mask.o
