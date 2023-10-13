#include<unistd.h>

int main(){
	execlp("ls", "ls", "-l", "linx_programming", (char *)0);
}
