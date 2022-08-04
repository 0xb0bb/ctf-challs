CFLAGS=-s -Wno-int-conversion -m32 -fno-pic -fno-stack-protector
SRC=chall16.c
OBJ=$(SRC:.c=.o)
BIN=chall16
 
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