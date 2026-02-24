CC = gcc
CFLAGS = -O3 -Wall
OBJECTS = main.o poly.o

.PHONY: clean

main.exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o main.exe -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f main.o poly.o main.exe

	