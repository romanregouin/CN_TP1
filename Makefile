CC = gcc
CFLAGS = -g -Wall -Werror -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXE = entropie Huffman

all: $(EXE)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

entropie : entropie.o
	$(CC) $(CFLAGS) -o $@ $^

Huffman : Huffman.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean

clean:
	rm -f $(EXE) $(OBJ)
