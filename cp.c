#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
void cp(int src, int dest) {
  int n;
  char ch;
  while((n = read(src, &ch, sizeof(char))) > 0) {
    if (write(dest, &ch, n) != n) {
      printf(1, "cp: write error\n");
      exit();
    }

  }
  if(n < 0){
    printf(1, "cp: read error\n");
    exit();
  }
}
/* Consideration: 
 * 1. argv[1] will contain source file 
 * 2. argv[2] will contain dest file 
 */
int main(int argc, char *argv[]) {
	
	if (argc < 3) {
		printf(1, "cp: Syntax Error correct syntax is: cp src dest\n");
		return 0;
	}
	int src = open(argv[1], 0);
	int dest = open(argv[2], O_CREATE | O_WRONLY);

	cp(src, dest);
    exit();
}
