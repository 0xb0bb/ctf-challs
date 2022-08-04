CFLAGS=-s -z relro -z now -fno-stack-protector -Wno-format-security # -no-pie -fno-pic
SRC=chall07.c
OBJ=$(SRC:.c=.o)
BIN=$(SRC:.c=)

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