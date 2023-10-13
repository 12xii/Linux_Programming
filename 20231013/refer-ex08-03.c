#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
	int x, y, status, sum = 1;

	scanf("%d %d", &x, &y);

	pid_t p = fork();
	
	if(p > 0){
		wait(&status);
		sum = (int)pow(x, y);
		status >>= 8;
		printf("%d\n", status - sum);
	} else if (p == 0) {
		pid_t q = fork();
		
		if(q > 0) {
			wait(&status);
			status >>= 8;
			sum = 0;
			for(int i = x; i <= y; i++){
				sum += i;
			}
			sum = status - sum;
			exit(sum);
		} else if (q == 0){
			for(int i = x; i <= y; i++){
				sum *= i;
			}
			exit(sum);
		} else printf("fail to fork!\n");
	} else printf("fail to fork!\n");
}
