CFLAGS=-s -no-pie -fno-pic -fstack-protector-all -z noexecstack -Wall -Wno-parentheses -Wstack-protector -ansi -O2
SRC=chall06.c
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