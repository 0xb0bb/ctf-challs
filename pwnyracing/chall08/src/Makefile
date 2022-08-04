CFLAGS=-s -z relro -z now -fstack-protector-all -no-pie -fno-pic -O0
SRC=chall08.c
OBJ=$(SRC:.c=.o)
BIN=chall08

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