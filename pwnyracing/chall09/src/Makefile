CC=arm-linux-gnueabihf-gcc-4.8
CFLAGS=-s -z relro -z now -fstack-protector-all -marm -O0
SRC=chall09.c
OBJ=$(SRC:.c=.o)
BIN=chall09

.PHONY : clean

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