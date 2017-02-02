CC = gcc
CFLAGS = -I. -Wall
LFLAGS = -lm
PROG = shell.out

all: utils.o
	$(CC) -o $(PROG) $(CFLAGS) main.c utils.o

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm *.o 
	rm *~
