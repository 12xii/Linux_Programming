#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
	pid_t pid;

	int i, sum = 0;
	scanf("%d", &i);

	pid = fork();

	if(pid > 0){
		for(int j = 1 ; j <= i ; j++){
			sum += j;
		}

		printf("%d\n", sum);
	}

	else if (pid == 0) {
		sum = 1;
		for(int j = 1 ; j <= i ; j++){
			sum *= j;
		}
		printf("%d\n", sum);
	}
	else printf("error!");
}
