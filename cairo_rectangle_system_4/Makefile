FILES := cairo-rectangles
CC := gcc
CFLAGS := -g -Wall -pedantic -I /usr/include/cairo -c
LFLAGS := -g -Wall -pedantic 

main: $(FILES)
	@echo "Building done"
	xviewer cairo-rectangles.png

$(FILES):$@
	@echo "Compiling: " $@
	gcc $(CFLAGS) $@.c -o $@.o
	@echo "Link: " $@
	gcc $(LFLAGS) $@.o -lcairo -o $@
	@echo "Run: " $@
	./$@

clean:
	rm $(FILES) *.o *.png 
