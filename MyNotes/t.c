#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main() {
	int count = 0;
	for (count = 0; count < 3; count++) {
		if (fork() == 0) {
			printf("Os\n");
		}
	}
	return 0;
}
