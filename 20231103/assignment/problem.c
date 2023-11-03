#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	putenv("MYDATA=5");
	
	execl("newProcess", "newProcess", (char *)0);
}
