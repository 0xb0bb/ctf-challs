CC=gcc

CFLAGS=-fstack-protector-all -Wno-unused-label -Wno-incompatible-pointer-types -Wno-int-to-pointer-cast -fomit-frame-pointer
LFLAGS=-lz
SRC=chall02.c
OBJ=$(SRC:.c=.o)
BIN=chall02

all:
	$(MAKE) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LFLAGS)

.o:
	$(CC) $(CFLAGS) $< -o $@

challenge: all
	rm -f $(OBJ)

clean:
	rm -f $(BIN) $(OBJ)