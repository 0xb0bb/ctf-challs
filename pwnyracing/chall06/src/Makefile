CFLAGS=-z relro -z now -fno-stack-protector -Wno-format-security # -no-pie -fno-pic
SRC=chall06.c
OBJ=$(SRC:.c=.o)
BIN=chall06

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