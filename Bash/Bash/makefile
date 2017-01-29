CC = gcc
CFLAGS = -I. -Wall
LFLAGS = -lm
PROG = out

all: history.o history.h
	$(CC) -o $(PROG) $(CFLAGS) main.c history.o 

history.o: history.c
	$(CC) $(CFLAGS) -c history.c

clean:
	rm *.o 
	rm *~
