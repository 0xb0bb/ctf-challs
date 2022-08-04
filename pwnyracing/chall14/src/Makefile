CFLAGS=-s -fstack-protector-all -Wno-incompatible-pointer-types -Wno-int-conversion
SRC=chall14.c
OBJ=$(SRC:.c=.o)
BIN=chall14

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