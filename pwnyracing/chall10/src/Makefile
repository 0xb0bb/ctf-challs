CFLAGS=-s -z,relro -no-pie -fno-pic -fno-stack-protector -Wno-implicit-function-declaration
SRC=chall10.c
OBJ=$(SRC:.c=.o)
BIN=chall10

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