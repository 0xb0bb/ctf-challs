CC=gcc

CFLAGS=-s -m32 -no-pie -fstack-protector-all -Wno-sequence-point-Wall -Wno-unused-variable
SRC=chall01.c
OBJ=$(SRC:.c=.o)
BIN=chall01

all:
	$(MAKE) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@

challenge: all
	rm -f $(OBJ)

clean:
	rm -f $(BIN) $(OBJ)