CFLAGS=-m32 -no-pie -fno-pic -fno-stack-protector
SRC=chall17.c
OBJ=$(SRC:.c=.o)
BIN=chall17

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