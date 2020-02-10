CC = gcc
CFLAGS =-g -Wall -Werror
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXE = entropie Huffman

all: $(EXE)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

entropie : entropie.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

Huffman : Huffman.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

.PHONY : clean

clean:
	rm -f $(EXE) $(OBJ)
