#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define SIZE 4

void child(int *fd_F, int *fd_C) {
    char c[SIZE];

    while(1) {
        read(fd_C[0], c, SIZE);
        if (strcmp(c, "end") == 0) {
            break;
        }
        fprintf(stdout, "I'm the child (PID = %d)\n", getpid());
        write(fd_F[1], "msg", SIZE);
    }
}

void father(int *fd_F, int *fd_C) {
    int i;
    char c[SIZE];

    if (fork() == 0) {
        child(fd_F, fd_C);
        exit(0);
    }

    for(i = 0; 1; i++) {
        fprintf(stdout, "I'm the father (PID = %d)\n", getpid());
        
        if (i > 3) {
            write(fd_C[1], "end", SIZE);
            break;
        }
        write(fd_C[1], "msg", SIZE);
        read(fd_F[0], c, SIZE);
    }

}

int main() {
    int fd_F[2], fd_C[2], *status;

    if (pipe(fd_F) != 0) {
        fprintf(stdout, "La pipe è fallita.");
        exit(1);
    }

    if (pipe(fd_C) != 0) {
        fprintf(stdout, "La pipe è fallita.");
        exit(1);
    }

    father(fd_F, fd_C);

    wait(status);

    return 0;
}