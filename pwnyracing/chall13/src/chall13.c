#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 0x20
#define MAX_CMD 0x400

#define CMD "$PROG '%s'"

char command[MAX_CMD];

void banner(){

    puts("pwny.racing presents...\n\n\e[31;1m\e[47m▄\e[0m\e[31;1m█████████▄\e" \
    "[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███     \e[31;1m\e[47m▄\e[0m\e[31;1m███"  \
    "\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███   \e[31;1m\e[47m▄\e[0m\e[31;1m███"  \
    "\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m██████████\e[0m        \e[31;1m\e[47m▄" \
    "\e[0m\e[31;1m████████▄\e[0m  \e[31;1m\e[47m▄\e[0m\e[31;1m███\e[0m\n\e[31" \
    ";1m████\e[41;1m▀▀▀████\e[0m \e[31;1m████     ████\e[0m \e[31;1m█████▄ ██" \
    "██\e[0m \e[31;1m\e[41;1m▀▀▀▀▀▀█████\e[0m        \e[31;1m████\e[41;1m▀▀██" \
    "██\e[0m\e[31;1m▄\e[0m \e[31;1m████\e[0m\n\e[31;1m████▄▄▄████\e[0m \e[31;" \
    "1m████  ▄  ████\e[0m \e[31;1m███████████\e[0m     \e[31;1m▄████\e[41;1m▀" \
    "\e[0m\e[31m▀\e[0m \e[37;1m▄\e[0m\e[31;1m▄▄▄▄▄\e[0m \e[31;1m████  \e[0m\e" \
    "[31m▀\e[31;1m████\e[0m \e[31;1m████\e[0m\n\e[31;1m██████████\e[41;1m▀\e[" \
    "0m \e[31;1m████▄███▄████\e[0m \e[31;1m████\e[0m\e[31m▀\e[31;1m\e[41;1m▀█" \
    "████\e[0m   \e[31;1m▄████\e[41;1m▀\e[0m\e[31m▀\e[0m   \e[31;1m██████\e[0" \
    "m \e[31;1m████   ████\e[0m \e[31;1m████\e[0m\n\e[31;1m████\e[0m\e[31m▀▀▀" \
    "▀▀▀\e[0m  \e[31;1m\e[41;1m██████▀██████\e[0m \e[31;1m████  \e[0m\e[31m▀"  \
    "\e[31;1m████\e[0m \e[31;1m▄████\e[41;1m▀\e[0m\e[31m▀\e[0m     \e[31m▀▀▀▀" \
    "▀▀\e[0m \e[31;1m████▄▄████\e[41;1m▀\e[0m \e[37;1m\e[41;1m▄\e[31;1m▄▄▄\e[" \
    "0m\n\e[31;1m████\e[0m        \e[31;1m████\e[41;1m▀\e[0m\e[31m▀\e[0m \e[3" \
    "1m▀\e[0m\e[31;1m\e[41;1m▀████\e[0m \e[31;1m████   ████\e[0m \e[31;1m████" \
    "\e[0m\e[31m▀\e[0m              \e[31;1m█████████\e[41;1m▀\e[0m  \e[31;1m" \
    "████\e[0m\n\e[31m▀▀▀▀\e[0m        \e[31m▀▀▀▀     ▀▀▀▀\e[0m \e[31m▀▀▀▀   " \
    "▀▀▀▀\e[0m \e[31m▀▀▀▀\e[0m               \e[31m▀▀▀▀▀▀▀▀▀\e[0m   \e[31m▀▀▀" \
    "▀\e[0m\n                                                    speedrun edi" \
    "tion 4/5!\n");

    puts("\e[1mlist:\e[0m ");
    system("/bin/ls -A1 *.txt");
    puts("");
}

int input(char *dest){

    int i = 0;
    int n = read(0, dest, MAX_CMD);

    for (i = 0; i < n; i++)
        if (dest[i] == '\n' || dest[i] == '\r' || dest[i] == '\'' || dest[i] == '/' || dest[i] == '\\')
            dest[i] = '\0';

    snprintf(command, MAX_CMD, CMD, dest);
    return n;
}

int main(){

    char *buffer = alloca(MAX_BUF);

    memset(buffer, 0, MAX_BUF);
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);

    alarm(60);
    banner();

    while (1){

        printf("\e[1mfile:\e[0m ");
        if (input(buffer) <= 0)
            continue;

        system(command);
        usleep(500000);
    }

    return EXIT_SUCCESS;
}