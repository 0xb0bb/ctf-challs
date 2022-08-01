#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char template[0x20]              = "/tmp/covid-YYYY-XXXXXX";
static char        table_64[]    = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static signed char index_64[128] =
{
    -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,62, -1,-1,-1,63,
    52,53,54,55, 56,57,58,59, 60,61,-1,-1, -1,-1,-1,-1,
    -1, 0, 1, 2,  3, 4, 5, 6,  7, 8, 9,10, 11,12,13,14,
    15,16,17,18, 19,20,21,22, 23,24,25,-1, -1,-1,-1,-1,
    -1,26,27,28, 29,30,31,32, 33,34,35,36, 37,38,39,40,
    41,42,43,44, 45,46,47,48, 49,50,51,-1, -1,-1,-1,-1
};

#define CHAR64(c)   (((c) < 0 || (c) > 127) ? -1 : index_64[(c)])
#define MAX_SIZE    8192
#define MAX_ROWS    128

#define MAX_DATA    0x400

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

struct data {
    char   data[MAX_DATA];
    char  *ptr;
    bool   debug;
    char   file[0x20];
};

char *decode(const char *value, int vlen, size_t *rlen){

    *rlen = 0;
    int c1, c2, c3, c4;

    char *result =(char *) malloc(vlen);
    char *out = result;

    while (1){
        if (value[0] == 0)
            return result;

        c1 = value[0];
        if (CHAR64(c1) == -1)
            goto decode_error;;

        c2 = value[1];
        if (CHAR64(c2) == -1)
            goto decode_error;;

        c3 = value[2];
        if ((c3 != '=') && (CHAR64(c3) == -1))
            goto decode_error;;

        c4 = value[3];
        if ((c4 != '=') && (CHAR64(c4) == -1))
            goto decode_error;;

        value += 4;
        *out++ = (CHAR64(c1) << 2) | (CHAR64(c2) >> 4);
        *rlen += 1;
        if (c3 != '='){
            *out++ = ((CHAR64(c2) << 4) & 0xf0) | (CHAR64(c3) >> 2);
            *rlen += 1;
            if (c4 != '='){
                *out++ = ((CHAR64(c3) << 6) & 0xc0) | CHAR64(c4);
                *rlen += 1;
            }
        }
    }

decode_error:
    printf("\x1b[31;1mfailed:\x1b[0m cannot decode: %s\n", value);
    free(result);
    result = NULL;
    *rlen = 0;
    return result;
}

void banner(){

    puts("                                                    \xf0\x9f\x91"   \
    "\x91  \xf0\x9f\x91\x91\n                                               " \
    "       \xf0\x9f\x91\x91\n \x1b[34;1m▄\x1b[47m▄\x1b[0m\x1b[34;1m████████" \
    "▄\x1b[0m \x1b[34;1m\x1b[47m▄\x1b[0m\x1b[34;1m█████████▄\x1b[0m \x1b[34;" \
    "1m▄\x1b[47m▄\x1b[0m\x1b[34;1m████████▄\x1b[0m \x1b[34;1m\x1b[47m▄\x1b[0" \
    "m\x1b[34;1m███   \x1b[34;1m\x1b[47m▄\x1b[0m\x1b[34;1m███\x1b[0m \x1b[34" \
    ";1m▄\x1b[47m▄\x1b[0m\x1b[34;1m████████▄\x1b[0m\n \x1b[34;1m████\x1b[43;" \
    "1m▀▀▀████\x1b[0m \x1b[34;1m████\x1b[43;1m▀▀▀████\x1b[0m \x1b[34;1m████"  \
    "\x1b[43;1m▀▀▀████\x1b[0m \x1b[34;1m█████▄ ████\x1b[0m \x1b[34;1m████"    \
    "\x1b[43;1m▀▀▀████\x1b[0m\n \x1b[34;1m████   ████\x1b[0m \x1b[34;1m████▄" \
    "▄▄███\x1b[43;1m▀\x1b[0m \x1b[34;1m████   ████\x1b[0m \x1b[34;1m████████" \
    "███\x1b[0m \x1b[34;1m████▄▄▄████\x1b[0m\n \x1b[34;1m████   ████\x1b[0m " \
    "\x1b[34;1m████\x1b[43;1m▀▀▀███\x1b[0m\x1b[34;1m▄\x1b[0m \x1b[34;1m████ " \
    "  ████\x1b[0m \x1b[34;1m████\x1b[0m\x1b[33m▀\x1b[34;1m\x1b[43;1m▀█████"  \
    "\x1b[0m \x1b[34;1m████\x1b[43;1m▀▀▀████\x1b[0m\n \x1b[34;1m████▄▄▄████"  \
    "\x1b[0m \x1b[34;1m████   ████\x1b[0m \x1b[34;1m████▄▄▄████\x1b[0m \x1b[" \
    "34;1m████  \x1b[0m\x1b[33m▀\x1b[34;1m████\x1b[0m \x1b[34;1m████   ████"  \
    "\x1b[0m\n \x1b[34;1m\x1b[43;1m▀█████████▀\x1b[0m \x1b[34;1m████   ████"  \
    "\x1b[0m \x1b[34;1m\x1b[43;1m▀█████████▀\x1b[0m \x1b[34;1m████   ████"    \
    "\x1b[0m \x1b[34;1m████   ████\x1b[0m\n  \x1b[33m▀▀▀\x1b[0m\x1b[34;1m███" \
    "\x1b[0m\x1b[33m▀▀▀\x1b[0m  \x1b[33m▀▀▀▀   ▀▀▀▀\x1b[0m  \x1b[33m▀▀▀▀▀▀▀▀" \
    "▀\x1b[0m  \x1b[33m▀▀▀▀   ▀▀▀▀\x1b[0m \x1b[33m▀▀▀▀   ▀▀▀▀\x1b[0m\n     "  \
    "\x1b[33m▀▀▀\x1b[0m             qr decoding for the socially distant...\n");
}

void make_template(){

    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0){
        printf("\x1b[31;1mfailed:\x1b[0m cannot open /dev/urandom\n");
        exit(EXIT_FAILURE);
    }

    char   c = 0;
    size_t n = 0;
    char  *p = strstr(template, "YYYY");

    while (n < 4 && read(fd, &c, 1)){
        if ((c >= 0x41 && c <= 0x5a) ||
            (c >= 0x61 && c <= 0x6a) ||
            (c >= 0x30 && c <= 0x39)){
            *p++ = c;
            n++;
        }
    }
}

void init(){

    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);

    make_template();
}

int make_tempfile(char *file){

    int  fd;
    char path[0x20] = "";
    char tmpf[0x20] = "";

    strncpy(tmpf, template, sizeof(tmpf));
    fd = mkstemp(tmpf);
    if (fd < 0)
        return fd;

    snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);
    realpath(path, file);

    return fd;
}

int check_str(char *file){

    unsigned char c;
    while ((c = *file) && (isalnum(c) || c == '-' || c == '/'))
        file++;

    return *file == '\0';
}

void main(int argc, char *argv[], char *envp[]){

    int fd;
    int n;

    char  *decoded;
    size_t size;
    char   cmd[0x50];

    struct data data;
    data.ptr   = (void *) &data.data;
    data.debug = (argc > 1 && strcmp(argv[1], "debug") == 0)? true: false;

    init();
    banner();

    while (1){

        fd = make_tempfile((void *) &data.file);
        if (fd < 0){
            perror("\x1b[31;1mfailed:\x1b[0m mkstemp()");
            exit(EXIT_FAILURE);
        }

        if (data.debug == true)
            printf("\x1b[1mtmpnam:\x1b[0m %s\n", data.file);

        printf("\x1b[1mbase64:\x1b[0m ");
        n = read(STDIN_FILENO, data.data, MAX_DATA * 4);
        if (data.data[n-1] == '\n')
            data.data[n-1] = '\0';

        if ((decoded = decode(data.data, sizeof(data.data), &size)) == NULL)
            goto softfail;

        if (write(fd, decoded, MIN(size, MAX_DATA)) == -1){
            perror("\x1b[31;1mfailed:\x1b[0m write()");
            exit(EXIT_FAILURE);
        }

        if (strncmp(data.file, template, 16) != 0)
            exit(EXIT_FAILURE);

        if (check_str(data.file) == 0)
            exit(EXIT_FAILURE);

        putchar('\n');
        printf("\x1b[1moutput:\x1b[0m\n");
        snprintf(cmd, 0x50, "/usr/bin/zbarimg --raw '%s'", data.file);
        system(cmd);

        free(decoded);

softfail:

        printf("\npress [enter] to continue...\n");  
        getchar();

        close(fd);

        if (strncmp(data.file, template, 16) != 0)
            exit(EXIT_FAILURE);

        unlink(data.file);
        continue;
    }

    puts("hej då");
    _exit(EXIT_SUCCESS);
}