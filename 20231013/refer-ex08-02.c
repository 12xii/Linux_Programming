#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int x, y, status;
	scanf("%d %d", &x, &y);
	pid_t p = fork();

	if(p > 0) {
		wait(&status);
		printf("%d\n", ((int)pow(x, y) + (status >> 8)));
	} else if(p == 0) {
		int sum = 0;
		for(int i = x ; i <= y; i++){
			sum += i;
		}
		exit(sum);
	} else printf("fail to fork\n");
	printf("exit\n");
}
