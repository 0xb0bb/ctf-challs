#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <alloca.h>
 
#define MAX_TRIES 5
#define MAX_BUFF  0x50
 
#define EPERM  1
#define ENOENT 2
 
struct File {
    int   size;
    FILE *file; 
};
 
void banner(){
 
    char *clear = alloca(0x100);
    memset(clear, '\0', 0x100);
 
    puts("                                pwny.racng presents...\n\n\e[38;5;2" \
    "07m\e[48;5;15m▄\e[0m\e[38;5;207m█████████▄\e[0m \e[38;5;207m\e[48;5;15m▄" \
    "\e[0m\e[38;5;207m███     \e[38;5;207m\e[48;5;15m▄\e[0m\e[38;5;207m███\e[" \
    "0m \e[38;5;207m\e[48;5;15m▄\e[0m\e[38;5;207m███   \e[38;5;207m\e[48;5;15" \
    "m▄\e[0m\e[38;5;207m███\e[0m \e[38;5;207m▄\e[48;5;15m▄\e[0m\e[38;5;207m██" \
    "██████▄\e[0m \e[38;5;207m\e[48;5;15m▄\e[0m\e[38;5;207m███\e[0m\n\e[38;5;" \
    "207m████\e[48;5;14m▀▀▀████\e[0m \e[38;5;207m████     ████\e[0m \e[38;5;2" \
    "07m█████▄ ████\e[0m \e[38;5;207m\e[48;5;14m████▀▀▀████\e[0m \e[38;5;207m" \
    "████\e[0m\n\e[38;5;207m████▄▄▄████\e[0m \e[38;5;207m████  ▄  ████\e[0m "  \
    "\e[38;5;207m███████████\e[0m \e[38;5;207m████▄▄▄████\e[0m \e[38;5;207m██" \
    "██\e[0m\n\e[38;5;207m██████████\e[48;5;14m▀\e[0m \e[38;5;207m████▄███▄██" \
    "██\e[0m \e[38;5;207m████\e[0m\e[36;1m▀\e[38;5;207m\e[48;5;14m▀█████\e[0m" \
    " \e[38;5;207m\e[48;5;14m▀██████████\e[0m \e[38;5;207m████\e[0m\n\e[38;5;" \
    "207m████\e[0m\e[36;1m▀▀▀▀▀▀\e[0m  \e[38;5;207m\e[48;5;14m██████▀██████\e" \
    "[0m \e[38;5;207m████  \e[0m\e[36;1m▀\e[38;5;207m████\e[0m  \e[36;1m▀▀▀▀▀" \
    "▀\e[0m\e[38;5;207m████\e[0m \e[37;1m\e[48;5;14m▄\e[38;5;207m▄▄▄\e[0m\n\e" \
    "[38;5;207m████\e[0m        \e[38;5;207m████\e[48;5;14m▀\e[0m\e[36;1m▀\e[" \
    "0m \e[36;1m▀\e[0m\e[38;5;207m\e[48;5;14m▀████\e[0m \e[38;5;207m████   ██" \
    "██\e[0m        \e[38;5;207m████\e[0m \e[38;5;207m████\e[0m\n\e[36;1m▀▀▀▀" \
    "\e[0m        \e[36;1m▀▀▀▀     ▀▀▀▀\e[0m \e[36;1m▀▀▀▀   ▀▀▀▀\e[0m        " \
    "\e[36;1m▀▀▀▀\e[0m \e[36;1m▀▀▀▀\e[0m\n");
}
 
int open_file(const char *file, struct File *nfo){
 
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        return -ENOENT;
 
    nfo->file = fdopen(fd, "r");
 
    fseek(nfo->file, 0, SEEK_END);
    nfo->size = ftell(nfo->file);
    fseek(nfo->file, 0, SEEK_SET);
 
    if (strstr(file, "/dev") != NULL || strstr(file, "/proc") != NULL)
        return -EPERM;
 
    return 0;
 
}
 
void read_file(FILE *fp, int size){
 
    char pad[MAX_BUFF];
    int  i = 0;
    char c = 0;
 
 
    while((c = fgetc(fp)) != EOF && c != '\n' && c != '\r')
        pad[i++] = c;
 
    if (c == '\n')
        pad[i] = '\0';
 
    printf("data: %s\n", pad);
}
 
int main(int argc, char *argv[]){
 
    char   name[256] = "";
    struct File nfo;
    
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
 
    alarm(60);
    banner();
 
    for (int i = 0; i < MAX_TRIES; i++){
 
        memset(name, '\0', sizeof name);
        if (printf("file: ") && fgets(name, 256, stdin) == NULL)
            break;
 
        name[strlen(name)-1] = '\0';
        if (strlen(name) == 0)
            break;
 
        if (open_file(name, &nfo) == -EPERM){
            printf("\e[31;1mnope:\e[0m don't even think about it.\n");
            continue;
        }
 
        if (nfo.file == NULL){
            printf("\e[31;1mnope:\e[0m file could not be opened for reading.\n");
            continue;
        }
 
        read_file(nfo.file, nfo.size);
 
        if (nfo.file != NULL)
            fclose(nfo.file);
    }
 
    return EXIT_SUCCESS;
}