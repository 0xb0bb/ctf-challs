#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILE_LEN 0x80

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
    "\e[0m \e[37;1m▄\e[0m\e[31;1m▄▄▄▄▄\e[0m \e[31;1m████   \e[41;1m▀▀▀▀\e[0m " \
    "\e[31;1m████\e[0m\n\e[31;1m██████████\e[41;1m▀\e[0m \e[31;1m████▄███▄███" \
    "█\e[0m \e[31;1m████\e[0m\e[31m▀\e[31;1m\e[41;1m▀█████\e[0m   \e[31;1m▄██" \
    "██\e[41;1m▀\e[0m\e[31m▀\e[0m   \e[31;1m██████\e[0m \e[31;1m████   ▄▄▄▄\e" \
    "[0m \e[31;1m████\e[0m\n\e[31;1m████\e[0m\e[31m▀▀▀▀▀▀\e[0m  \e[31;1m\e[41" \
    ";1m██████▀██████\e[0m \e[31;1m████  \e[0m\e[31m▀\e[31;1m████\e[0m \e[31;" \
    "1m▄████\e[41;1m▀\e[0m\e[31m▀\e[0m     \e[31m▀▀▀▀▀▀\e[0m \e[31;1m████▄▄▄█" \
    "███\e[0m \e[37;1m\e[41;1m▄\e[31;1m▄▄▄\e[0m\n\e[31;1m████\e[0m        \e[" \
    "31;1m████\e[41;1m▀\e[0m\e[31m▀\e[0m \e[31m▀\e[0m\e[31;1m\e[41;1m▀████\e[" \
    "0m \e[31;1m████   ████\e[0m \e[31;1m████\e[0m\e[31m▀\e[0m              "  \
    "\e[31;1m\e[41;1m▀█████████▀\e[0m \e[31;1m████\e[0m\n\e[31m▀▀▀▀\e[0m     " \
    "   \e[31m▀▀▀▀     ▀▀▀▀\e[0m \e[31m▀▀▀▀   ▀▀▀▀\e[0m \e[31m▀▀▀▀\e[0m      " \
    "          \e[31m▀▀▀▀▀▀▀▀▀\e[0m  \e[31m▀▀▀▀\e[0m\n                       " \
    "                             speedrun edition 3/5!");
}

void fatal(const char *msg){

    printf("\e[31;1mnope:\e[0m %s\n", msg);
    _exit(EXIT_FAILURE);
}

void read_file(char *file){

    FILE  *fp;
    char  *op;
    long   sk;
    size_t sz;

    if ((fp = fopen(file, "r")) == NULL)
        fatal("could not open file for reading.");

    printf("size: ");
    scanf("%ul%*c", (unsigned int *) &sz);

    if ((op = calloc(sz, 1)) == NULL)
        fatal("could not allocate memory for output.");

    printf("seek: ");
    scanf("%li%*c", &sk);
    fseek(fp, sk, SEEK_SET);

    fread(op, 1, sz, fp);
    printf("data: ");
    fwrite(op, sz, 1, stdout);
    puts("");

    free(op);
    fclose(fp);
}

void write_file(char *file){

    FILE  *fp;
    char  *op;
    long   sk;
    size_t sz;

    if ((fp = fopen(file, "a+")) == NULL)
        fatal("could not open file for writing.");

    printf("size: ");
    scanf("%ul%*c", (unsigned int *) &sz);

    if ((op = calloc(sz, 1)) == NULL)
        fatal("could not allocate memory for output.");

    printf("seek: ");
    scanf("%li%*c", &sk);
    fseek(fp, sk, SEEK_SET);

    printf("data: ");
    fread(op, 1, sz, stdin);
    fwrite(op, sz, 1, fp);

    free(op);
    fclose(fp);
}

int main(){

    int option = 0;
    char file[FILE_LEN] = "";
	
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);

    alarm(60);
    banner();

    while (1){

        printf("\n\e[1;1mOptions: \e[0m\n   1) read\n   2) write\n\n");
        printf("> ");

        scanf("%d%*c", &option);
        if (option < 1 || option > 2)
            _exit(EXIT_FAILURE);

        printf("file: ");
        if (fgets(file, FILE_LEN, stdin) == NULL)
            _exit(EXIT_FAILURE);
        if (file[strlen(file)-1] == '\n')
            file[strlen(file)-1] = '\x00';

        (option == 1)? read_file(file): write_file(file);
    }

    return EXIT_SUCCESS;
}