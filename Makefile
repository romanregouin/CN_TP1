CC = gcc
CFLAGS = -g -Wall -Werror -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXE = entropie

all: $(EXE)

%.o = %.c
	$(CC) $(CFLAGS) -c $<

entropie : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean

clean:
	rm -f $(EXE) $(OBJ)
