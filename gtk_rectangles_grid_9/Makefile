FILES := gtk-rectangles-grid draw_coords draw_rectangles
CC := gcc
MISC-CFLAGS := -g -Wall -pedantic -I /usr/include/cairo
MISC-LFLAGS := -g -Wall -pedantic
CAIRO-CFLAGS := -I /usr/include/cairo
CAIRO-LFLAGS := -lcairo -lm
GTK-CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK-LFLAGS = $(shell pkg-config --libs gtk+-3.0)

main: $(FILES)
	@echo "Building done"
	@echo "Link: " $@
	$(CC) $(MISC-LFLAGS)  gtk-rectangles-grid.o draw_coords.o draw_rectangles.o -o gtk-rectangles-grid $(GTK-LFLAGS) $(CAIRO-LFLAGS)

$(FILES):$@
	@echo "Compiling: " $@
	$(CC) $(MISC-CFLAGS) $(GTK-CFLAGS) $(CAIRO-CFLAGS) -c $@.c -o $@.o
	#@echo "Link: " $@
	#$(CC) $(MISC-LFLAGS) $@.o -o $@ $(GTK-LFLAGS) $(CAIRO-LFLAGS)
	#@echo "Run: " $@
	#./$@

clean:
	rm -f $(FILES) *.o 
