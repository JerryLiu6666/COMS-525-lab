CC = gcc
CFLAGS = -Wall -O3 -std=c99 -fopenmp
LFLAGS = -lgomp

all: main.exe

main.exe: blur.o
	$(CC) blur.o -o main.exe $(LFLAGS)

blur.o: blur.c
	$(CC) $(CFLAGS) -c blur.c

clean:
	rm -f *.o main.exe
