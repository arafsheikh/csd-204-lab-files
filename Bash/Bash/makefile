CC = gcc
CFLAGS = -I. -Wall
LFLAGS = -lm
PROG = out

all: history.o execute.o
	$(CC) -o $(PROG) $(CFLAGS) main.c history.o execute.o

execute.o: execute.c
	$(CC) $(CFLAGS) -c execute.c

history.o: history.c
	$(CC) $(CFLAGS) -c history.c

clean:
	rm *.o 
	rm *~
