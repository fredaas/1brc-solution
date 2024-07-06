CC=gcc
CFLAGS=-std=c99 -Wall -O0 -g -I.
OBJ=main.o solution_1.o

.PHONY : clean all

all : clean main gendata

main : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

gendata : gendata.o
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ) : %.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean :
	rm -rf *.o main gendata
