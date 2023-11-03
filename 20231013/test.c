#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	printf("ppid : %d\npid : %d\n", getppid(), getpid());
}
