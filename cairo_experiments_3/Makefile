FILES := cairo-hello stroke fill showtext paint mask setsourcergba setsourcegradient path-close textextents diagram draw tips-ellipse-1 tips-letter tips-font
CC := gcc
CFLAGS := -g -Wall -pedantic -I /usr/include/cairo -c
LFLAGS := -g -Wall -pedantic 

main: $(FILES)
	@echo "Building done"

$(FILES):$@
	@echo "Compiling: " $@
	gcc $(CFLAGS) $@.c -o $@.o
	@echo "Link: " $@
	gcc $(LFLAGS) $@.o -lcairo -o $@
	@echo "Run: " $@
	./$@

clean:
	rm $(FILES) *.o *.png *.svg
