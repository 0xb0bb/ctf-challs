# For compiling on ARM system
CC=gcc

# For cross compiling
#CC=arm-linux-gnueabi-gcc

CFLAGS=-m32 -pie -Wl,-z,relro,-z,now -fstack-protector-all -z noexecstack -Wall -Wno-format-security -Wstack-protector -ansi
LDFLAGS=
SRC=chall04.c
OBJ=$(SRC:.c=.o)
BIN=chall04

.PHONY : clean

all:
	$(MAKE) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@

challenge: all
	rm -f $(OBJ)

clean:
	rm -f $(BIN) $(OBJ)