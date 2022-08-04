#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF 0x10

int play(){

	char buf[MAX_BUF];
	return read(STDIN_FILENO, &buf, 0x30);
}

int main(){
	
	play();
	return EXIT_SUCCESS;
}