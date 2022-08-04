#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef long long * BLOCK;

#define MAX_BUFF 0x20
#define MAX_NUMS 0x10

char input[MAX_BUFF];

void banner(){

    write(STDOUT_FILENO, "                               pwny.racing presents" \
    "...\n\n\e[36;1m\e[47m▄\e[0m\e[36;1m█████████▄\e[0m \e[36;1m\e[47m▄\e[0m"  \
    "\e[36;1m███     \e[36;1m\e[47m▄\e[0m\e[36;1m███\e[0m \e[36;1m\e[47m▄\e[0" \
    "m\e[36;1m███   \e[36;1m\e[47m▄\e[0m\e[36;1m███\e[0m \e[36;1m▄\e[47m▄\e[0" \
    "m\e[36;1m█████████\e[0m \e[36;1m\e[47m▄\e[0m\e[36;1m███\e[0m\n\e[36;1m██" \
    "██\e[46;1m▀▀▀████\e[0m \e[36;1m████     ████\e[0m \e[36;1m█████▄ ████\e[" \
    "0m \e[36;1m\e[46;1m████▀▀▀▀▀▀▀\e[0m \e[36;1m████\e[0m\n\e[36;1m████▄▄▄██" \
    "██\e[0m \e[36;1m████  ▄  ████\e[0m \e[36;1m███████████\e[0m \e[36;1m████" \
    "▄▄▄▄▄▄\e[0m  \e[36;1m████\e[0m\n\e[36;1m██████████\e[46;1m▀\e[0m \e[36;1" \
    "m████▄███▄████\e[0m \e[36;1m████\e[0m\e[36m▀\e[36;1m\e[46;1m▀█████\e[0m " \
    "\e[36;1m\e[46;1m████▀▀▀████\e[0m \e[36;1m████\e[0m\n\e[36;1m████\e[0m\e[" \
    "36m▀▀▀▀▀▀\e[0m  \e[36;1m\e[46;1m██████▀██████\e[0m \e[36;1m████  \e[0m\e" \
    "[36m▀\e[36;1m████\e[0m \e[36;1m████▄▄▄████\e[0m \e[37;1m\e[46;1m▄\e[36;1" \
    "m▄▄▄\e[0m\n\e[36;1m████\e[0m        \e[36;1m████\e[46;1m▀\e[0m\e[36m▀\e[" \
    "0m \e[36m▀\e[0m\e[36;1m\e[46;1m▀████\e[0m \e[36;1m████   ████\e[0m \e[36" \
    ";1m\e[46;1m▀█████████▀\e[0m \e[36;1m████\e[0m\n\e[36m▀▀▀▀\e[0m        \e" \
    "[36m▀▀▀▀     ▀▀▀▀\e[0m \e[36m▀▀▀▀   ▀▀▀▀\e[0m  \e[36m▀▀▀▀▀▀▀▀▀\e[0m  \e[" \
    "36m▀▀▀▀\e[0m\n\n\e[1;1mSum Calculator\e[0m\n", 0x6b3);
}

int main(int argc, char *argv[]){

    int value = 0;
    int total = 0;

    int n = 0;

    int nums[MAX_NUMS] = {
    	0, 0, 0, 0, 0, 0, 0, 0,
    	0, 0, 0, 0, 0, 0, 0, 0
    };
    int *ptr = nums;

    alarm(60);
    banner();
    sleep(1);

    while (1){

        write(STDOUT_FILENO, "<< ", 3);
        n = read(STDIN_FILENO, input, MAX_BUFF);
        *((BLOCK) input+(n-1)) = 0x00;

        value = 0;
        value = atoi(input);

        if (n == 0 || input[0] == '=')
            break;

        *ptr++ = value;
    }

    ptr = nums;
    while (*ptr)
        total += *ptr++;

    printf("\e[1mresult:\e[0m %d\n", total);
    return EXIT_SUCCESS;
}