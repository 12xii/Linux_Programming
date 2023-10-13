#include <unistd.h>
#include <stdio.h>

int main() {
	execl("1", "apple", "option", (char *)0);	
}

