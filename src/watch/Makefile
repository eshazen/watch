all: watch

# include needed for OS-X
CFLAGS = -I/usr/X11/include

#CFLAGS = -DDEBUG

clean:
	rm -f *.o *~ calc

watch.o: watch.c watch.h

watch_cb.o: watch_cb.c watch.h 

watch_main.o: watch_main.c watch.h

display_list.o: display_list.c display_list.h

watch: watch_main.o watch.o watch_cb.o display_list.o
	cc -o watch $^ -lforms
