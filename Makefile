CC=gcc
OPTS=-Wall -pedantic -std=c11

objects=client.o \
		send.o \
		program.o \
		receive.o \
		server.o

all: main

main: build $(objects) program
	@echo project compiled

%.o: %.c
	$(CC) $(OPTS) -c $< -o build/$@

program: client.c send.c receive.c server.c program.c
	$(CC) $(OPTS) -o build/$@ $^

build:
	@mkdir build

clean:
	rm -rf build *.o