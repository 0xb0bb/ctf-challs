#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 0x80

void banner(){
	
    puts("pwny.racing presents...\n\n\e[31;1m\e[47m▄\e[0m\e[31;1m█████████▄\e" \
    "[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███     \e[31;1m\e[47m▄\e[0m\e[31;1m███"  \
    "\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███   \e[31;1m\e[47m▄\e[0m\e[31;1m███"  \
    "\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m██████████\e[0m        \e[31;1m\e[47m▄" \
    "\e[0m\e[31;1m█████████▄\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███\e[0m\n\e[31" \
    ";1m████\e[41;1m▀▀▀████\e[0m \e[31;1m████     ████\e[0m \e[31;1m█████▄ ██" \
    "██\e[0m \e[31;1m\e[41;1m▀▀▀▀▀▀█████\e[0m        \e[31;1m████\e[41;1m▀▀▀█" \
    "███\e[0m \e[31;1m████\e[0m\n\e[31;1m████▄▄▄████\e[0m \e[31;1m████  ▄  ██" \
    "██\e[0m \e[31;1m███████████\e[0m     \e[31;1m▄████\e[41;1m▀\e[0m\e[31m▀"  \
    "\e[0m \e[37;1m▄\e[0m\e[31;1m▄▄▄▄▄\e[0m \e[31;1m████▄▄▄███\e[41;1m▀\e[0m " \
    "\e[31;1m████\e[0m\n\e[31;1m██████████\e[41;1m▀\e[0m \e[31;1m████▄███▄███" \
    "█\e[0m \e[31;1m████\e[0m\e[31m▀\e[31;1m\e[41;1m▀█████\e[0m   \e[31;1m▄██" \
    "██\e[41;1m▀\e[0m\e[31m▀\e[0m   \e[31;1m██████\e[0m \e[31;1m████\e[41;1m▀" \
    "▀▀███\e[0m\e[31;1m▄\e[0m \e[31;1m████\e[0m\n\e[31;1m████\e[0m\e[31m▀▀▀▀▀" \
    "▀\e[0m  \e[31;1m\e[41;1m██████▀██████\e[0m \e[31;1m████  \e[0m\e[31m▀\e[" \
    "31;1m████\e[0m \e[31;1m▄████\e[41;1m▀\e[0m\e[31m▀\e[0m     \e[31m▀▀▀▀▀▀"  \
    "\e[0m \e[31;1m████▄▄▄████\e[0m \e[37;1m\e[41;1m▄\e[31;1m▄▄▄\e[0m\n\e[31;" \
    "1m████\e[0m        \e[31;1m████\e[41;1m▀\e[0m\e[31m▀\e[0m \e[31m▀\e[0m\e" \
    "[31;1m\e[41;1m▀████\e[0m \e[31;1m████   ████\e[0m \e[31;1m████\e[0m\e[31" \
    "m▀\e[0m              \e[31;1m██████████▀\e[0m \e[31;1m████\e[0m\n\e[31m▀" \
    "▀▀▀\e[0m        \e[31m▀▀▀▀     ▀▀▀▀\e[0m \e[31m▀▀▀▀   ▀▀▀▀\e[0m \e[31m▀▀" \
    "▀▀\e[0m               \e[31m▀▀▀▀▀▀▀▀▀▀\e[0m  \e[31m▀▀▀▀\e[0m\n          " \
    "                                          speedrun edition 2/5!\n");
}

void main(){

    char buffer[BUF_SIZE] = "";
	
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);

    alarm(60);
    banner();

    printf("input: ");
    fgets(buffer, BUF_SIZE, stdin);

    printf(buffer);
    exit(EXIT_SUCCESS);
}