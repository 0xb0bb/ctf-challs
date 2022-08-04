#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_RETRY     24
#define MAX_STRING    13
#define MAX_BUFFER  1024
#define MAX_PADDING   16

#define PADDING do {char *mem = alloca(MAX_PADDING); memset(mem, '\0', MAX_PADDING);} while(0);

char data[MAX_BUFFER];

void clear(char *c[]){

    if (!c)
        return; 

    char **var;
    char  *ptr;

    for (var = c; *var != NULL; var++)
        for (ptr = *var; *ptr != 0; *ptr++ = 0/*, ptr++*/, *var = 0);

    var = 0;
    ptr = 0;
}

void banner(){

    puts("                                pwny.racng presents...\n\n\e[32;1m\e[47m▄\e[0m\e[32;1m█" \
    "████████▄\e[0m \e[32;1m\e[47m▄\e[0m\e[32;1m███     \e[32;1m\e[47m▄\e[0m\e[32;1m███\e[0m \e[3" \
    "2;1m\e[47m▄\e[0m\e[32;1m███   \e[32;1m\e[47m▄\e[0m\e[32;1m███\e[0m \e[32;1m\e[47m▄\e[0m\e[32" \
    ";1m███   \e[32;1m\e[47m▄\e[0m\e[32;1m███\e[0m \e[32;1m\e[47m▄\e[0m\e[32;1m███\e[0m\n\e[32;1m" \
    "████\e[42;1m▀▀▀████\e[0m \e[32;1m████     ████\e[0m \e[32;1m█████▄ ████\e[0m \e[32;1m████   " \
    "████\e[0m \e[32;1m████\e[0m\n\e[32;1m████▄▄▄████\e[0m \e[32;1m████  ▄  ████\e[0m \e[32;1m███" \
    "████████\e[0m \e[32;1m████▄▄▄████\e[0m \e[32;1m████\e[0m\n\e[32;1m██████████\e[42;1m▀\e[0m "  \
    "\e[32;1m████▄███▄████\e[0m \e[32;1m████\e[0m\e[32m▀\e[32;1m\e[42;1m▀█████\e[0m \e[32;1m\e[42" \
    ";1m▀██████████\e[0m \e[32;1m████\e[0m\n\e[32;1m████\e[0m\e[32m▀▀▀▀▀▀\e[0m  \e[32;1m\e[42;1m█" \
    "█████▀██████\e[0m \e[32;1m████  \e[0m\e[32m▀\e[32;1m████\e[0m  \e[32m▀▀▀▀▀▀\e[0m\e[32;1m████" \
    "\e[0m \e[37;1m\e[42;1m▄\e[32;1m▄▄▄\e[0m\n\e[32;1m████\e[0m        \e[32;1m████\e[42;1m▀\e[0m" \
    "\e[32m▀\e[0m \e[32m▀\e[0m\e[32;1m\e[42;1m▀████\e[0m \e[32;1m████   ████\e[0m        \e[32;1m" \
    "████\e[0m \e[32;1m████\e[0m\n\e[32m▀▀▀▀\e[0m        \e[32m▀▀▀▀     ▀▀▀▀\e[0m \e[32m▀▀▀▀   ▀▀" \
    "▀▀\e[0m        \e[32m▀▀▀▀\e[0m \e[32m▀▀▀▀\e[0m\n");
}

int again(){

    int  n = 0;
    char retry[MAX_RETRY];

    printf("retry? (yes sir/nope): ");
    if (retry[(n = read(0, retry, MAX_RETRY))-1] == '\n')
        retry[n-1] = '\0';

    return strncmp("yes sir", retry, MAX_RETRY) == 0;
}

int input(){

    PADDING;
    printf("input: ");

    read(0, data, MAX_BUFFER);
    return strlen(data) <= MAX_STRING;
}

int output(){

    register long long *rdx asm("rdx");
    register long long *rsp asm("rsp");

    PADDING;
    printf("output: ");

    rdx = 0;
    *(rsp+3) = 0;

    printf(data);
    return again();
}

int play(){

    PADDING;

    if (!input())
        _exit(0);

    return output();
}

int main(int argc, char *argv[], char *envp[]){

    register long long *rsp asm("rsp");
    *(rsp+7) = (long long) &_exit;

    PADDING;
    
    clear(argv);
    clear(envp);

    alarm(60);
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);

    banner();
    while (1){

        if (!play())
            break;
    }

    return 0;
}