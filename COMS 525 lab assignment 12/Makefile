CC = gcc
CFLAGS = -O3 -Wall
LDFLAGS = -lm

OBJECTS = main.o \
	BisectionStack.o \
	Push.o \
	Pop.o \
	Peek.o \
	GetStackSize.o \
	DisplayStack.o \
	DeleteStack.o

main.exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o main.exe $(LDFLAGS)

%.o: %.c node.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe

