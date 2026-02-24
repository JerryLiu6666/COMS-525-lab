CC = gcc
CFLAGS = -O3 -Wall
LFLAGS =
OBJECTS = main.o poly.o

.PHONY: clean

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe

	