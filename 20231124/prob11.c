#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
		pid_t pid = fork();

		if(pid > 0) {
			// 부모	
			printf("file1: hello! (%d)\n", getpid());
			fd_read = open(file1, O_RDONLY);
			buffer = (char *)(malloc(sizeof(char) * pipe_size));
		}
		else {
						
		}
}

// 파이프를 통해 전송되어야 하는 데이터의 크기가 파이프의 용량을 초과한다면 데이터를 나누어 전송해야 한다.
// 부모 프로세스에서 임의의 파일을 읽어 파일의 크기를 확인한 후 파이프의 크기에 맞추어 전송하고
// 자식 프로세스는 받은 데이터를 다른 파일에 복사하여라.
