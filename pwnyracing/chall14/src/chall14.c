#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

unsigned int c = 0;
unsigned int n = 0;

void clear(char *c[]){

    if (!c)
        return; 

    char **var;
    char  *ptr;

    for (var = c; *var != NULL; var++)
        for (ptr = *var; *ptr != 0; *ptr++ = 0, *var = 0);

    var = 0;
    ptr = 0;
}

void banner(){

    puts("pwny.racing presents...\n\n\e[31;1m\e[47m▄\e[0m\e[31;1m█████████▄\e" \
    "[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███     \e[31;1m\e[47m▄\e[0m\e[31;1m███"  \
    "\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███   \e[31;1m\e[47m▄\e[0m\e[31;1m███"  \
    "\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m██████████\e[0m        \e[31;1m▄\e[47m" \
    "▄\e[0m\e[31;1m█████████\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███\e[0m\n\e[31" \
    ";1m████\e[41;1m▀▀▀████\e[0m \e[31;1m████     ████\e[0m \e[31;1m█████▄ ██" \
    "██\e[0m \e[31;1m\e[41;1m▀▀▀▀▀▀█████\e[0m        \e[31;1m████\e[41;1m▀▀▀▀" \
    "▀▀▀\e[0m \e[31;1m████\e[0m\n\e[31;1m████▄▄▄████\e[0m \e[31;1m████  ▄  ██" \
    "██\e[0m \e[31;1m███████████\e[0m     \e[31;1m▄████\e[41;1m▀\e[0m\e[31m▀"  \
    "\e[0m \e[37;1m▄\e[0m\e[31;1m▄▄▄▄▄\e[0m \e[31;1m████▄▄▄\e[0m     \e[31;1m" \
    "████\e[0m\n\e[31;1m██████████\e[41;1m▀\e[0m \e[31;1m████▄███▄████\e[0m "  \
    "\e[31;1m████\e[0m\e[31m▀\e[31;1m\e[41;1m▀█████\e[0m   \e[31;1m▄████\e[41" \
    ";1m▀\e[0m\e[31m▀\e[0m   \e[31;1m██████\e[0m \e[31;1m████\e[41;1m▀▀▀\e[0m" \
    "     \e[31;1m████\e[0m\n\e[31;1m████\e[0m\e[31m▀▀▀▀▀▀\e[0m  \e[31;1m\e[4" \
    "1;1m██████▀██████\e[0m \e[31;1m████  \e[0m\e[31m▀\e[31;1m████\e[0m \e[31" \
    ";1m▄████\e[41;1m▀\e[0m\e[31m▀\e[0m     \e[31m▀▀▀▀▀▀\e[0m \e[31;1m████▄▄▄" \
    "▄▄▄▄\e[0m \e[37;1m\e[41;1m▄\e[31;1m▄▄▄\e[0m\n\e[31;1m████\e[0m        \e" \
    "[31;1m████\e[41;1m▀\e[0m\e[31m▀\e[0m \e[31m▀\e[0m\e[31;1m\e[41;1m▀████\e" \
    "[0m \e[31;1m████   ████\e[0m \e[31;1m████\e[0m\e[31m▀\e[0m              " \
    "\e[31;1m\e[41;1m▀██████████\e[0m \e[31;1m████\e[0m\n\e[31m▀▀▀▀\e[0m     " \
    "   \e[31m▀▀▀▀     ▀▀▀▀\e[0m \e[31m▀▀▀▀   ▀▀▀▀\e[0m \e[31m▀▀▀▀\e[0m      " \
    "          \e[31m▀▀▀▀▀▀▀▀▀▀\e[0m \e[31m▀▀▀▀\e[0m\n                       " \
    "                             speedrun edition 5/5!\n");
}

void win(char *arg2, char *arg1, char *bin){

    char *argx[] = { bin, arg1, arg2, NULL };
    char *envx[] = { NULL };

    execve(argx[0], argx, envx);
}

void quit(){

    _exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[], char *envp[]){

    register long long *rsp asm("rsp");
    *(rsp+15) = (long long) &quit;
    *(rsp+32) = (long long) 0;

    char buffer[0x40];
    
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);

    alarm(60);
    banner();

    clear(argv);
    clear(envp);

    while (1){

        printf("buffer: ");

        c = 0; n = 0;
        while ((c = fgetc(stdin)) != EOF && c != '\n' && c != '\r' && n <= 0x200)
            buffer[n++] = c;

        if (n == 0)
            break;

        printf("output: %s\n", buffer);
    }

    register long long *rdi asm("rdi") = -1;
    register long long *rsi asm("rsi") = -1;
    register long long *rdx asm("rdx") = -1;

    return EXIT_SUCCESS;
}