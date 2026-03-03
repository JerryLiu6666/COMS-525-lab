CC = gcc
CFLAGS = -O3 -Wall -std=c99
LDFLAGS = -lm

OBJECTS = main.o matrix.o

main.exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o main.exe $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe
