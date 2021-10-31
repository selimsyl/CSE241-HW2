
CC=g++
# CFLAGS will be the options passed to the compiler.
CFLAGS=-c -std=c++11 -Wall

OBJECTS = peg.o

all: peg

peg: $(OBJECTS)
	$(CC) $(OBJECTS) -o peg

%.o: %.cpp
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o *.out

run:
	./peg