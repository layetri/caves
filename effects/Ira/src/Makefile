CC = g++
CFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack

all: example

example : jack_module.o main.o Pan.o Filter.o Buffer.o LowPassFilter.o
	$(CC) -o $@ $(CFLAGS) jack_module.o Pan.o main.o Filter.o Buffer.o LowPassFilter.o $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f example