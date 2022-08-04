CC=gcc

CFLAGS=-s -z noexecstack -nostdlib -no-pie -fno-pic -Tdata=0x06000000
LFLAGS=
SRC=chall03.S
OBJ=$(SRC:.S=.o)
BIN=chall03

all:
	$(MAKE) $(BIN)
	@/usr/bin/printf '\x89\xdc\x37\xcd\x80\xcb' | dd of=$(BIN) bs=1 seek=308 count=6 conv=notrunc

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LFLAGS)

.o:
	$(CC) $(CFLAGS) $< -o $@

challenge: all
	rm -f $(OBJ)

clean:
	rm -f $(BIN) $(OBJ)