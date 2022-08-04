#include <stdio.h>
#include <string.h>

#define LOGIN_LIMIT     5
#define LOGIN_PASSWD    "pwnyr4c3"

int checkpass(char *pass){

    if (strcmp(pass, LOGIN_PASSWD) == 0)
        return 0;

    return -1;
}

int login(char *fmt){

    char pass[128];
    printf("pass: ");
    fflush(stdout);

    if (scanf(fmt, pass))
        if (checkpass(pass) == 0)
            return 0;

    printf(pass); printf(" is incorrect\n");

    return -1;
}

int shell(){

    printf("/* I knew I forgot to code something... */\n");
    return 0;
}

void banner(){

    puts("\n                               pwny.racing presents...\n");

    puts("\x1b[1;35m\x1b[47m▄█████████\x1b[0m\x1b[1;35m▄\x1b[0m \x1b[1;35m\x1b[4"    \
    "7m▄███\x1b[0m     \x1b[1;35m\x1b[47m▄███\x1b[0m \x1b[1;35m\x1b[47m▄███\x1b[0m " \
    "  \x1b[1;35m\x1b[47m▄███\x1b[0m \x1b[1;35m\x1b[47m▄█████████\x1b[0m\x1b[1;35m▄" \
    "\x1b[0m \x1b[1;35m\x1b[47m▄███\x1b[0m\n\x1b[0;45m\x1b[1;35m████▀▀▀████\x1b[0m " \
    "\x1b[1;35m████     ████\x1b[0m \x1b[1;35m█████▄ ████\x1b[0m \x1b[0;45m\x1b[1;3" \
    "5m▀▀▀▀▀▀▀████\x1b[0m \x1b[1;35m████\x1b[0m\n\x1b[1;35m████▄▄▄████\x1b[0m \x1b[" \
    "1;35m████  ▄  ████\x1b[0m \x1b[1;35m███████████\x1b[0m \x1b[1;35m    ▄▄▄███"    \
    "\x1b[0;45m\x1b[1;35m▀\x1b[0m \x1b[1;35m████\x1b[0m\n\x1b[1;35m██████████\x1b[0" \
    ";45m\x1b[1;35m▀\x1b[0m \x1b[1;35m████▄███▄████\x1b[0m \x1b[1;35m████\x1b[45m▀"  \
    "\x1b[0m\x1b[1;35m██████\x1b[0m     \x1b[0;45m\x1b[1;35m▀▀▀███\x1b[0m\x1b[1;35m" \
    "▄\x1b[0m \x1b[1;35m████\x1b[0m\n\x1b[1;35m████\x1b[0;35m▀▀▀▀▀▀\x1b[0m  \x1b[1;" \
    "35m██████\x1b[0;45m\x1b[1;35m▀██████\x1b[0m \x1b[1;35m████\x1b[0m \x1b[35m▀"    \
    "\x1b[0m\x1b[0;45m\x1b[1;35m▀████\x1b[0m \x1b[1;35m▄▄▄▄▄▄▄████\x1b[0m \x1b[0;45" \
    "m\x1b[1;35m▀▀▀▀\x1b[0m\n\x1b[1;35m████\x1b[0m        \x1b[1;35m████\x1b[0;45m"  \
    "\x1b[1;35m▀\x1b[0;35m▀\x1b[0m \x1b[0;35m▀\x1b[1;35m\x1b[0;45m\x1b[1;35m▀████"   \
    "\x1b[0m \x1b[1;35m████\x1b[0m   \x1b[1;35m████\x1b[0m \x1b[1;35m██████████\x1b" \
    "[0;45m\x1b[1;35m▀\x1b[0m \x1b[1;35m████\x1b[0m\n\x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0" \
    "m        \x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0m     \x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0m "  \
    "\x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0m   \x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0m \x1b[0;45m"   \
    "\x1b[1;35m▀▀▀▀▀▀▀▀▀▀\x1b[0m  \x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0m\n");
}

void clearenv(char *argv[], char *envp[]){

    char** arg;
    char*  c;

    for (arg = argv; *arg; arg++)
        for (c = *arg; *c; c++)
            *c = '\0';

    for (arg = envp; *arg; arg++)
        for (c = *arg; *c; c++)
            *c = '\0';

    *argv = 0;
    *envp = 0;
}

int main(int argc, char *argv[], char *envp[]){

    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);

    char fmt[8];
    strcpy(fmt, "%12s");

    banner();
    clearenv(argv, envp);

    int i;
    for (i = 0; i < LOGIN_LIMIT; i++)
        if (login(fmt) == 0)
            if (shell() == 0)
                break;

    if (i == LOGIN_LIMIT)
        printf("\x1b[31;1merror:\x1b[0m too many attempts!\n");

    return 0;
}