#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void banner(){
	
    puts("pwny.racing presents...\n\n\e[31;1m\e[47m▄\e[0m\e[31;1m█████████▄\e" \
    "[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███     \e[31;1m\e[47m▄\e[0m\e[31;1m███"  \
    "\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███   \e[31;1m\e[47m▄\e[0m\e[31;1m███"  \
    "\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m██████████\e[0m        \e[31;1m▄\e[47m" \
    "▄\e[0m\e[31;1m████████▄\e[0m \e[31;1m\e[47m▄\e[0m\e[31;1m███\e[0m\n\e[31" \
    ";1m████\e[41;1m▀▀▀████\e[0m \e[31;1m████     ████\e[0m \e[31;1m█████▄ ██" \
    "██\e[0m \e[31;1m\e[41;1m▀▀▀▀▀▀█████\e[0m        \e[31;1m████\e[41;1m▀▀▀█" \
    "███\e[0m \e[31;1m████\e[0m\n\e[31;1m████▄▄▄████\e[0m \e[31;1m████  ▄  ██" \
    "██\e[0m \e[31;1m███████████\e[0m     \e[31;1m▄████\e[41;1m▀\e[0m\e[31m▀"  \
    "\e[0m \e[37;1m▄\e[0m\e[31;1m▄▄▄▄▄\e[0m \e[31;1m████▄▄▄████\e[0m \e[31;1m" \
    "████\e[0m\n\e[31;1m██████████\e[41;1m▀\e[0m \e[31;1m████▄███▄████\e[0m "  \
    "\e[31;1m████\e[0m\e[31m▀\e[31;1m\e[41;1m▀█████\e[0m   \e[31;1m▄████\e[41" \
    ";1m▀\e[0m\e[31m▀\e[0m   \e[31;1m██████\e[0m \e[31;1m████\e[41;1m▀▀▀████"  \
    "\e[0m \e[31;1m████\e[0m\n\e[31;1m████\e[0m\e[31m▀▀▀▀▀▀\e[0m  \e[31;1m\e[" \
    "41;1m██████▀██████\e[0m \e[31;1m████  \e[0m\e[31m▀\e[31;1m████\e[0m \e[3" \
    "1;1m▄████\e[41;1m▀\e[0m\e[31m▀\e[0m     \e[31m▀▀▀▀▀▀\e[0m \e[31;1m████  " \
    " ████\e[0m \e[37;1m\e[41;1m▄\e[31;1m▄▄▄\e[0m\n\e[31;1m████\e[0m        "  \
    "\e[31;1m████\e[41;1m▀\e[0m\e[31m▀\e[0m \e[31m▀\e[0m\e[31;1m\e[41;1m▀████" \
    "\e[0m \e[31;1m████   ████\e[0m \e[31;1m████\e[0m\e[31m▀\e[0m            " \
    "  \e[31;1m████   ████\e[0m \e[31;1m████\e[0m\n\e[31m▀▀▀▀\e[0m        \e[" \
    "31m▀▀▀▀     ▀▀▀▀\e[0m \e[31m▀▀▀▀   ▀▀▀▀\e[0m \e[31m▀▀▀▀\e[0m            " \
    "   \e[31m▀▀▀▀   ▀▀▀▀\e[0m \e[31m▀▀▀▀\e[0m\n                             " \
    "                       speedrun edition 1/5!\n");
}

int main(){

    char buffer[0x10];
	
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);

    alarm(60);
    banner();

    printf("input: ");
    gets(buffer);

    return EXIT_SUCCESS;
}