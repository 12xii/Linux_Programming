#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void int_handle(int);
int num = 0;

int main(){
	static struct sigaction act;
	act.sa_handler = int_handle;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);
	
	while(1){
		printf("I'm sleepy...\n");
		sleep(1);
		if(num >= 1) exit(0);
	}
}

void int_handle(int signum) {
	char buf[1024] = "exit";
	int fd;

	fd = open("a.txt", O_CREAT | O_EXCL, 0644);
	write(fd, buf, 1024);
	num++;
}
