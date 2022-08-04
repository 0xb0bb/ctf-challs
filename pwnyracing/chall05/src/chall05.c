#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

#define MAX_GUYS    255
#define MAX_NAME    48
#define MAX_DESC    1024

#define CMD_ADD     "add"
#define CMD_DEL     "del"
#define CMD_SHOW    "show"
#define CMD_EDIT    "edit"
#define CMD_SCORE   "inc"
#define CMD_TOP     "lead"
#define CMD_LEAD    "top"
#define CMD_QUIT    "quit"

typedef struct {
    uint32_t index;
    uint32_t score;
    char     name[MAX_NAME];
    char    *desc;
} guy;

typedef struct {
    guy  *guy;
    char alias[16];
} alias;

guy   *guys[MAX_GUYS];
guy   *freed[MAX_GUYS];
alias *akas[MAX_GUYS];
int    next  = 0;
int    count = 0;

void error(const char *format, ...){

    printf("\033[31;1merror:\033[0m ");
    va_list vargs;
    va_start(vargs, format);
    vprintf(format, vargs);
    printf("\n");
    va_end(vargs);
}

void success(const char *format, ...){

    printf("\033[32;1msuccess:\033[0m ");
    va_list vargs;
    va_start(vargs, format);
    vprintf(format, vargs);
    printf("\n");
    va_end(vargs);
}

guy *find(char *a){

    uint32_t i;
    for (i = 0; i < MAX_GUYS; i++){
        if (akas[i])
            if (strcmp(akas[i]->alias, a) == 0)
                return ((guy *) akas[i]->guy);
    }

    return (guy *) 0;
}

guy *getguy(){

    if (count <= 0){
        error("no players");
        return 0;    
    }

    unsigned int i = 0;
    guy *curr = 0;

    while (curr == 0){
        printf("index: ");
        fflush(stdout);

        if (scanf("%3u", &i))
            if (i <= MAX_GUYS && guys[i] != 0)
                curr = guys[i];
            else
                error("no such player");
    }

    return curr;
}

int getname(char *name){

    name[0] = '\0';
    while (strlen(name) == 0){

        printf("player: ");
        fflush(stdout);

        if (fgets(name, MAX_NAME, stdin))
            name[strcspn(name, "\r\n")] = 0;
    }

    return strlen(name);
}

int getdesc(char *desc){

    desc[0] = '\0';
    while (strlen(desc) == 0){

        printf("desc: ");
        fflush(stdout);

        if (fgets(desc, MAX_DESC, stdin))
            desc[strcspn(desc, "\r\n")] = 0;
    }

    return strlen(desc);
}

uint32_t getscore(){

    uint32_t score = 0;

    while (score == 0){
        printf("score: ");
        fflush(stdout);

        if (scanf("%3u", &score))
            if (score <= 0 || score > 999){
                error("invalid score");
                score = 0;
            }
    }

    return score;
}

int add(char *aka){

    if (count >= MAX_GUYS){
        error("player limit exeeded");
        return -1;
    }

    if (find(aka) != 0){
        error("player exists");
        return -1;
    }

    char   name[MAX_NAME];
    char   desc[MAX_DESC];
    char  *str;
    guy  *newguy = 0;
    alias *newalias = 0;

    if (getname(name) <= 0)
        return -1;

    if (getdesc(desc) <= 0)
        return -1;

    newguy = malloc(sizeof(guy));
    if (!newguy){
        error("problem allocating memory for %s", name);
        return -1;
    }

    str = malloc(strlen(desc)+1);
    if (!str){
        error("problem allocating memory for %s", name);
        return -1;
    }

    newguy->index = next++;
    newguy->score = 0;
    newguy->desc  = str;
    memcpy(newguy->name, name, sizeof(name));
    memcpy(newguy->desc, desc, strlen(desc)+1);

    guys[newguy->index] = newguy;
    count++;

    if (strlen(aka) > 0){

        newalias = malloc(sizeof(alias));
        if (!newalias){
            error("problem allocating memory for %s", aka);
            return -1;
        }

        newalias->guy = newguy;
        memcpy(newalias->alias, aka, sizeof(newalias->alias));

        akas[newguy->index] = newalias;
    }

    if (!newalias)
        success("player added (index: %d; name: %s)", newguy->index, newguy->name);
    else
        success("player added (index: %d; name: %s; alias: %s)", newguy->index, newguy->name, newalias->alias);

    return 0;
}

int edit(guy *curr){

    if (!curr)
        if ((curr = getguy()) == 0)
            return -1;

    int  size;
    char name[MAX_NAME];
    char desc[MAX_DESC];

    if (getname(name) <= 0)
        return -1;

    if (getdesc(desc) <= 0)
        return -1;

    size = strlen(curr->desc);
    if (strlen(desc) > size){
        free(curr->desc);
        curr->desc = malloc(strlen(desc)+1);
        if (!curr->desc){
            error("problem allocating memory for %s", name);
            return -1;
        }
    }

    curr->score = getscore();
    memcpy(curr->name, name, sizeof(name));
    memcpy(curr->desc, desc, strlen(desc)+1);

    success("player updated (index: %d; name: %s)", curr->index, curr->name);

    return 0;
}

int del(guy *curr){

    if (!curr)
        if ((curr = getguy()) == 0)
            return -1;

    success("deleted %s", curr->name);

    char *desc = curr->desc;

    guys[curr->index] = 0;
    free(curr);
    free(desc);

    count--;

    return 0;
}

int show(guy *curr){

    if (!curr)
        if ((curr = getguy()) == 0)
            return -1;

    printf("\nplayer:\n");
    printf("    index:  %d\n", curr->index);
    printf("    player: %s\n", curr->name);
    printf("    desc:   %s\n", curr->desc);
    printf("    score:  %d\n", curr->score);

    return 0;
}

int score(guy *curr){

    if (!curr)
        if ((curr = getguy()) == 0)
            return -1;

    int score;
    if ((score = getscore()) == 0)
        return -1;

    curr->score += score;

    success("%s scored %u points (total: %u)", curr->name, score, curr->score);

    return 0;
}

int cmp (const void *a, const void *b){

    guy *ptr1 = *((guy **) a);
    guy *ptr2 = *((guy **) b);

    if (!ptr1 || !ptr2)
        return 0;

    if (ptr1->score > ptr2->score)
        return -1;

    if (ptr1->score < ptr2->score)
        return 1;

    return 0;
}

int top(){

    if (count <= 0){
        error("no players");
        return -1;    
    }

    puts("");

    int   i;
    guy *ptr = 0;
    guy *max = 0;

    i = 0;
    for (i = 0; i < MAX_GUYS; i++)
        if ((ptr = guys[i]) != 0)
            if (!max || ptr->score > max->score)
            max = ptr;

    if (max->score == 0)
        error("no points scored yet");
    else
        show(max);

    return 0;
}

int totals(){

    if (count <= 0){
        error("no players");
        return -1;    
    }

    int i, n = 1, l = 0;
    char *pad = "                                                 ";
    guy *curr;
    guy *sort[MAX_GUYS];

    for (i = 0, n = 0; i < MAX_GUYS; i++)
        sort[n++] = guys[i];

    qsort(sort, n, sizeof(guy *), cmp);

    for (i = 0, n = 1; i < MAX_GUYS; i++){
        curr = (guy *) sort[i];
        if (curr != 0){
            l = strlen(pad) - strlen(curr->name);
            printf("%3d. %s%.*s %5d\n", n++, curr->name, l, pad,  curr->score);
        }
    }

    return 0;
}

void quit(){

    printf("\ngame over...\n");
    exit(0);
}

void process(char *cmd, char *aka){

    guy *alias;

    if (strlen(cmd) == 0)
        return;

    if (strlen(aka) > 0)
        alias = find(aka);
    else
        alias = 0;

    if (strcmp(cmd, CMD_ADD) == 0){
        add(aka);
    } else
    if (strcmp(cmd, CMD_EDIT) == 0){
        edit(alias);
    } else
    if (strcmp(cmd, CMD_DEL) == 0){
        del(alias);
    } else
    if (strcmp(cmd, CMD_SHOW) == 0){
        show(alias);
    } else
    if (strcmp(cmd, CMD_SCORE) == 0){
        score(alias);
    } else
    if (strcmp(cmd, CMD_TOP) == 0){
        top();
    } else
    if (strcmp(cmd, CMD_LEAD) == 0){
        totals();
    } else
    if (strcmp(cmd, CMD_QUIT) == 0){
        quit();
    }
}

void menu(){

    printf("\n");
    printf(" \x1b[1;35mstuff:\033[0m\n\n");

    printf("    * add * edit *\n");
    printf("    * del * show *\n");
    printf("    * inc * lead *\n");
    printf("    * top * quit *\n");

    printf("\n");

    printf(" > ");
    fflush(stdout);
}

void banner(){

    puts("\n pwny.racing presents...\n");

    puts(" \x1b[1;35m\x1b[47m▄█████████\x1b[0m\x1b[1;35m▄\x1b[0m \x1b[1;35m\x1b[4"    \
    "7m▄███\x1b[0m     \x1b[1;35m\x1b[47m▄███\x1b[0m \x1b[1;35m\x1b[47m▄███\x1b[0m "  \
    "  \x1b[1;35m\x1b[47m▄███\x1b[0m \x1b[1;35m\x1b[47m▄█████████\x1b[0m\x1b[1;35m▄"  \
    "\x1b[0m \x1b[1;35m\x1b[47m▄███\x1b[0m\n \x1b[0;45m\x1b[1;35m████▀▀▀████\x1b[0m " \
    "\x1b[1;35m████     ████\x1b[0m \x1b[1;35m█████▄ ████\x1b[0m \x1b[0;45m\x1b[1;3"  \
    "5m▀▀▀▀▀▀▀████\x1b[0m \x1b[1;35m████\x1b[0m\n \x1b[1;35m████▄▄▄████\x1b[0m \x1b[" \
    "1;35m████  ▄  ████\x1b[0m \x1b[1;35m███████████\x1b[0m \x1b[1;35m    ▄▄▄███"     \
    "\x1b[0;45m\x1b[1;35m▀\x1b[0m \x1b[1;35m████\x1b[0m\n \x1b[1;35m██████████\x1b[0" \
    ";45m\x1b[1;35m▀\x1b[0m \x1b[1;35m████▄███▄████\x1b[0m \x1b[1;35m████\x1b[45m▀"   \
    "\x1b[0m\x1b[1;35m██████\x1b[0m     \x1b[0;45m\x1b[1;35m▀▀▀███\x1b[0m\x1b[1;35m"  \
    "▄\x1b[0m \x1b[1;35m████\x1b[0m\n \x1b[1;35m████\x1b[0;35m▀▀▀▀▀▀\x1b[0m  \x1b[1;" \
    "35m██████\x1b[0;45m\x1b[1;35m▀██████\x1b[0m \x1b[1;35m████\x1b[0m \x1b[35m▀"     \
    "\x1b[0m\x1b[0;45m\x1b[1;35m▀████\x1b[0m \x1b[1;35m▄▄▄▄▄▄▄████\x1b[0m \x1b[0;45"  \
    "m\x1b[1;35m▀▀▀▀\x1b[0m\n \x1b[1;35m████\x1b[0m        \x1b[1;35m████\x1b[0;45m"  \
    "\x1b[1;35m▀\x1b[0;35m▀\x1b[0m \x1b[0;35m▀\x1b[1;35m\x1b[0;45m\x1b[1;35m▀████"    \
    "\x1b[0m \x1b[1;35m████\x1b[0m   \x1b[1;35m████\x1b[0m \x1b[1;35m██████████\x1b"  \
    "[0;45m\x1b[1;35m▀\x1b[0m \x1b[1;35m████\x1b[0m\n \x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0" \
    "m        \x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0m     \x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0m "   \
    "\x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0m   \x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0m \x1b[0;45m"    \
    "\x1b[1;35m▀▀▀▀▀▀▀▀▀▀\x1b[0m  \x1b[0;45m\x1b[1;35m▀▀▀▀\x1b[0m\n");

    puts("                                   community challenge!\n");

    menu();
}

int main(){

    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);

    alarm(60);
    banner();

    char buf[48];
    char aka[16];
    char cmd[16];

    while (fgets(buf, sizeof(buf), stdin) != NULL){

        buf[strcspn(buf, "\r\n")] = 0;

        cmd[0] = '\0';
        aka[0] = '\0';

        sscanf(buf, "%15[^ \t.\n]%*c %15[^ \t.\n]%*c", cmd, aka);
        process(cmd, aka);

        if (strlen(buf) > 1)
            menu();
    }

    return 0;
}