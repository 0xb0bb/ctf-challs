CFLAGS=-s -Wl,-z,relro -m32 -no-pie -fno-pic -fstack-protector-all -Wno-format-security
SRC=chall11.c
OBJ=$(SRC:.c=.o)
BIN=chall11

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