#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define DEF_PORT 1337
#define MAX_PORT 0xffff
#define MIN_PORT 0x400
#define MAX_BUFF 0x100

void fatal(const char *msg){

    printf("\e[31;1merror:\e[0m %s\n", msg);
    _exit(EXIT_FAILURE);
}

void s3cr3t(){

    printf("/bin/sh");
    asm("int $0x80\nret\n");
}

void handle(int fd){

    char buffer[MAX_BUFF] = "";

    if (fd < 3)
        _exit(EXIT_FAILURE);

    write(fd, "                               pwny.racing presents...\n\n\e[3" \
    "0;1m\e[47m▄\e[0m\e[30;1m█████████▄\e[0m \e[30;1m\e[47m▄\e[0m\e[30;1m███ " \
    "    \e[30;1m\e[47m▄\e[0m\e[30;1m███\e[0m \e[30;1m\e[47m▄\e[0m\e[30;1m███" \
    "   \e[30;1m\e[47m▄\e[0m\e[30;1m███\e[0m \e[30;1m▄\e[47m▄\e[0m\e[30;1m███" \
    "█████▄\e[0m \e[30;1m\e[47m▄\e[0m\e[30;1m███\e[0m\n\e[30;1m████\e[40;1m▀▀" \
    "▀████\e[0m \e[30;1m████     ████\e[0m \e[30;1m█████▄ ████\e[0m \e[30;1m"  \
    "\e[40;1m████▀▀▀████\e[0m \e[30;1m████\e[0m\n\e[30;1m████▄▄▄████\e[0m \e[" \
    "30;1m████  ▄  ████\e[0m \e[30;1m███████████\e[0m \e[30;1m\e[40;1m▀███\e[" \
    "0m\e[30;1m▄▄▄███\e[40;1m▀\e[0m \e[30;1m████\e[0m\n\e[30;1m██████████\e[4" \
    "0;1m▀\e[0m \e[30;1m████▄███▄████\e[0m \e[30;1m████\e[0m\e[30m▀\e[30;1m\e" \
    "[40;1m▀█████\e[0m \e[30;1m▄███\e[40;1m▀▀▀\e[0m\e[30;1m███▄\e[0m \e[30;1m" \
    "████\e[0m\n\e[30;1m████\e[0m\e[30m▀▀▀▀▀▀\e[0m  \e[30;1m\e[40;1m██████▀██" \
    "████\e[0m \e[30;1m████  \e[0m\e[30m▀\e[30;1m████\e[0m \e[30;1m████▄▄▄███" \
    "█\e[0m \e[37;1m\e[40;1m▄\e[30;1m▄▄▄\e[0m\n\e[30;1m████\e[0m        \e[30" \
    ";1m████\e[40;1m▀\e[0m\e[30m▀\e[0m \e[30m▀\e[0m\e[30;1m\e[40;1m▀████\e[0m" \
    " \e[30;1m████   ████\e[0m \e[30;1m\e[40;1m▀█████████▀\e[0m \e[30;1m████"  \
    "\e[0m\n\e[30m▀▀▀▀\e[0m        \e[30m▀▀▀▀     ▀▀▀▀\e[0m \e[30m▀▀▀▀   ▀▀▀▀" \
    "\e[0m  \e[30m▀▀▀▀▀▀▀▀▀\e[0m  \e[30m▀▀▀▀\e[0m\n\n", 1728);

    write(fd, "buffer: ", 8);

    int  i = 0;
    char c = 0;

    for (i = 0; i < MAX_BUFF << 2; i++){
        if ((read(fd, &c, 1) != 1) || c == '\n')
            break;

        buffer[i] = c;
    }
}

int main(int argc, char *argv[]){

    pid_t pid;
    int listenfd, clientfd, clientlen, port = DEF_PORT;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    if (argc > 1)
        if ((port = atoi(argv[1])) > MAX_PORT || port < MIN_PORT)
            fatal("Bad port number");

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    
    if (bind(listenfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
        perror("\e[31;1merror:\e[0m");
        _exit(EXIT_FAILURE);
    }

    listen(listenfd, 0x10);
    signal(SIGCHLD, SIG_IGN);

    clientlen = sizeof(client_addr);

    while (1){

        printf("\e[1mstatus:\e[0m waiting for client\n");

        if ((clientfd = accept(listenfd,(struct sockaddr *) &client_addr, &clientlen)) < 0)
            fatal("cannot accept() connection");

        if ((pid = fork()) < 0)
            fatal("cannot fork() child");

        if (pid == 0){

            close(listenfd);
            handle(clientfd);

            write(clientfd, "\e[1mit is always darkest before dawn...\e[0m\n", 45);
            close(clientfd);

            sleep(1);
            exit(EXIT_SUCCESS);

        } else {

            close(clientfd);
        }
    }

    s3cr3t();
    return EXIT_SUCCESS;
}