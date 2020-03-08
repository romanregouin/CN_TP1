CC = gcc
CFLAGS =-g -Wall -Werror
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXE = entropie Huffman arithmetic_encoding

all: $(EXE)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

entropie : entropie.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

Huffman : Huffman.o fap.o arbre.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

arithmetic_encoding : arithmetic_encoding.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

.PHONY : clean

arithmetic_encoding.o : arithmetic_encoding.h

clean:
	rm -f $(EXE) $(OBJ)
