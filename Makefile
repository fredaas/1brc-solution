CC=gcc
CFLAGS=-std=c99 -Wall -O0 -g
OBJ=main.o

.PHONY : clean all

all : clean main

main : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ) : %.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean :
	rm -rf *.o main
