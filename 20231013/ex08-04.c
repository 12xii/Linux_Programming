#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main(){
	pid_t p;
	int status = 0;
	if((p = fork()) > 0){
		while(!waitpid(p, &status, WNOHANG)){
			printf("parent: %d\n", status++);
			sleep(1);
		}
		printf("parent: child - exit(%d)\n", status);
	} else if (p == 0) {
		sleep(5);
		printf("bye!\n");
		exit(0);
	} else printf("fail to fork\n");
}
