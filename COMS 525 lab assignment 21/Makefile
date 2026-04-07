CC = mpicc
CFLAGS = -O3 -Wall -std=c99
OBJECTS = main.o

main.exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) *.exes