FILES := gtk-hello-window gtk-hello-world
CC := gcc
MISC-CFLAGS := -g -Wall -pedantic -I /usr/include/cairo
MISC-LFLAGS := -g -Wall -pedantic 
CAIRO-CFLAGS := -I /usr/include/cairo
CAIRO-LFLAGS := -lcairo
GTK-CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK-LFLAGS = $(shell pkg-config --libs gtk+-3.0)

main: $(FILES)
	@echo "Building done"

$(FILES):$@
	@echo "Compiling: " $@
	$(CC) $(MISC-CFLAGS) $(GTK-CFLAGS) $(CAIRO-CFLAGS) -c $@.c -o $@.o
	@echo "Link: " $@
	$(CC) $(MISC-LFLAGS) $@.o -o $@ $(GTK-LFLAGS) $(CAIRO-LFLAGS)
	#@echo "Run: " $@
	#./$@

clean:
	rm $(FILES) *.o 
