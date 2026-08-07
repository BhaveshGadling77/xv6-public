#include "types.h"
#include "user.h"
#include "fcntl.h"

#define DEFAULTLINES 10
char buff[1024];
int head(int fd, int lines) {
	char ch;
	int i = 0;
	int n;
	while ((n = read(fd, &ch, 1)) == 1 && lines > 0) {
		buff[i++] = ch;
		if (ch == '\n') {
			buff[i] = '\0';
			i = 0;
			printf(1, buff, strlen(buff));
			lines--;
		}
	}
	exit();
}
/* consideration:
 * 1. if only head <filepath> is given then it will print first 10 lines of it.
 * 2. only head <filepath> -n <no. of lines> is valide command. 
 */
int main(int argc, char *argv[]) {


	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		printf(1, "head: failed to open file.\n");
		exit();
	}
	if (argc == 2) {
		head(fd, DEFAULTLINES);
	} else if (argc == 4) {
		int lines = atoi(argv[3]);
		head(fd, lines);
	} else {
		printf(1, "head: Syntax Error.\n");
	}

	exit();
}
