CC = gcc
CFLAGS = -I. -Wall
LFLAGS = -lm
PROG = out

all: history.o executeFunctions.o
	$(CC) -o $(PROG) $(CFLAGS) main.c history.o executeFunctions.o

executeFunctions.o: executeFunctions.c
	$(CC) $(CFLAGS) -c executeFunctions.c

history.o: history.c
	$(CC) $(CFLAGS) -c history.c

clean:
	rm *.o 
	rm *~
