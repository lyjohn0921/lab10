CC=gcc
CFLAGS=-lWarn -pedantic

tempread.o:	tempread.c
	$(CC) $(CFLAGS) -c -ansi $<

tempread:	tempread.o
	cc tempread.o -o tempread

all:	tempread

clean:
	rm tempread *.o
