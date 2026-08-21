#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdio.h>

int main(int argc, char *argv[]) {

    int fd1, fd2 = 1, fd3 = 1, fd4 = 1;

    fd1 = open("./1", O_WRONLY | O_CREAT, S_IRUSR|S_IWUSR);
    fd2 = open("./2", O_RDONLY);
    fd3 = open("./3", O_WRONLY | O_CREAT, S_IRUSR|S_IWUSR);
    close(0);
    close(1);
    dup(fd2);
    dup(fd3);
    close(fd3);
    dup2(fd2, fd4);
    printf("%d %d %d %d\n", fd1, fd2, fd3, fd4);
    return 0;
}
