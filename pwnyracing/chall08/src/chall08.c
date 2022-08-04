#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

#define MAX_INPUT 1024 /* size of input buffer */
#define MAX_HSIZE   16 /* size of human readable filesize buffer */

typedef struct data {
    char input[MAX_INPUT];
    size_t n;
} data;

size_t i;
char   byte;
struct stat info;

void banner(){

    fprintf(stdout, "                               pwny.racing presents...\n" \
    "\n\e[34;1m\e[47m▄\e[0m\e[34;1m█████████▄\e[0m \e[34;1m\e[47m▄\e[0m\e[34;" \
    "1m███     \e[34;1m\e[47m▄\e[0m\e[34;1m███\e[0m \e[34;1m\e[47m▄\e[0m\e[34" \
    ";1m███   \e[34;1m\e[47m▄\e[0m\e[34;1m███\e[0m \e[34;1m\e[47m▄\e[0m\e[34;" \
    "1m██████████\e[0m \e[34;1m\e[47m▄\e[0m\e[34;1m███\e[0m\n\e[34;1m████\e[4" \
    "4;1m▀▀▀████\e[0m \e[34;1m████     ████\e[0m \e[34;1m█████▄ ████\e[0m \e[" \
    "34;1m████\e[44;1m▀▀▀▀▀▀▀\e[0m \e[34;1m████\e[0m\n\e[34;1m████▄▄▄████\e[0" \
    "m \e[34;1m████  ▄  ████\e[0m \e[34;1m███████████\e[0m \e[34;1m████▄▄▄▄▄▄" \
    "\e[0m  \e[34;1m████\e[0m\n\e[34;1m██████████\e[44;1m▀\e[0m \e[34;1m████▄" \
    "███▄████\e[0m \e[34;1m████\e[0m\e[34m▀\e[34;1m\e[44;1m▀█████\e[0m \e[34m" \
    "▀\e[0m\e[34;1m\e[44;1m▀▀▀▀▀▀████\e[0m \e[34;1m████\e[0m\n\e[34;1m████\e[" \
    "0m\e[34m▀▀▀▀▀▀\e[0m  \e[34;1m\e[44;1m██████▀██████\e[0m \e[34;1m████  \e" \
    "[0m\e[34m▀\e[34;1m████\e[0m \e[34;1m▄▄▄▄▄▄▄████\e[0m \e[37;1m\e[44;1m▄\e" \
    "[34;1m▄▄▄\e[0m\n\e[34;1m████\e[0m        \e[34;1m████\e[44;1m▀\e[0m\e[34" \
    "m▀\e[0m \e[34m▀\e[0m\e[34;1m\e[44;1m▀████\e[0m \e[34;1m████   ████\e[0m " \
    "\e[34;1m██████████\e[44;1m▀\e[0m \e[34;1m████\e[0m\n\e[34m▀▀▀▀\e[0m     " \
    "   \e[34m▀▀▀▀     ▀▀▀▀\e[0m \e[34m▀▀▀▀   ▀▀▀▀\e[0m \e[34m▀▀▀▀▀▀▀▀▀▀\e[0m" \
    "  \e[34m▀▀▀▀\e[0m\n");
    fflush(stdout);
}

char *filesize(double size, char *out){

    int i;
    const char *units[] = { "b", "kb", "mb", "gb", NULL };

    for(i = 0; size > 1024; size /= 1024, i++);
    sprintf(out, "%.*f%s", i, size, units[i]);

    return out;
}

void printinfo(char *filename, struct stat *info, FILE *output){

    char *path = realpath(filename, NULL);
    char  size[MAX_HSIZE];

    struct passwd *pw = getpwuid(info->st_uid);

    if (S_ISREG(info->st_mode)){

        memset(size, 0, MAX_HSIZE);
        filesize((double) info->st_size, size);

        fprintf(output, "\e[1;1mpath:\e[0m %s\n"    \
                        "\e[1;1mtype:\e[0m file\n"  \
                        "\e[1;1msize:\e[0m %s\n"    \
                        "\e[1;1muser:\e[0m %s\n\n",
                path, size, pw->pw_name);

    } else if (S_ISDIR(info->st_mode)){

        fprintf(output, "\e[1;1mpath:\e[0m %s\n"    \
                        "\e[1;1mtype:\e[0m dir\n"   \
                        "\e[1;1muser:\e[0m %s\n\n",
                path, pw->pw_name);

    } else {

        fprintf(stderr, "\e[31;1moops:\e[0m only regular files or directories.\n");
    }

    free(path);
}

void main(int argc, char *argv[]){
    
    FILE *out;

    struct data data;
    data.n = 0;

    banner();

    if (argc > 1){

        if ((out = fopen(argv[1], "a+")) == NULL){
            fprintf(stderr, "\e[31;1moops:\e[0m cannot open output file for writing.\n");
            _exit(EXIT_FAILURE);
        }

    } else {

        out = stdout;
    }

    fprintf(stdout, "file: ");
    fflush(stdout);

    while (!feof(stdin)){

        byte = fgetc(stdin);
        if (byte == '\n')
            break;

        i = data.n++;
        data.input[i] = byte;
    }

    data.input[data.n] = '\0';

    if (stat(data.input, &info) == 0){

        printinfo(data.input, &info, out);

    } else {

        fprintf(stderr, "\e[31;1moops:\e[0m file not found.\n");
    }

    fflush(out);

    if (fileno(out) > STDERR_FILENO)
        fclose(out);

    register long long *rcx asm("rcx") = 0;
    register long long *rdx asm("rdx") = 0;
    register long long *rdi asm("rdi") = 0;
    register long long *rsi asm("rsi") = 0;
    register long long  *r8 asm("r8")  = 0;
    register long long  *r9 asm("r9")  = 0;
}