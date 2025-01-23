#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 1024

typedef enum {
    receiver,
    sender
};

void consumer(int *fd) {
    int bytes, i;
    char str[BUF_SIZE];

    fprintf(stdout, "Consumer PID: %d\n", getpid());

    while(1) {
        bytes = read(fd[receiver], str, BUF_SIZE);
        
        if (strcmp(str, "end") == 0)
            break;

        for (i = 0; i < strlen(str); i++)
            str[i] = toupper(str[i]);
        fprintf(stdout, "Consumer: %s\n", str);
        fflush(stdout);
    }

    fprintf(stdout, "Terminando il consumatore...\n");
    exit(0);
}

void producer(int *fd) {
    char str[BUF_SIZE];

    fprintf(stdout, "Producer PID: %d\n", getpid());

    while(1) {
        sleep(1);
        fprintf(stdout, "Producer: ");
        fscanf(stdin, "%s", str);
        fflush(stdin);

        write(fd[sender], str, BUF_SIZE);

        if (strcmp(str, "end") == 0)
            break;
    }

    fprintf(stdout, "Terminando il produttore...\n");
    exit(0);
}

int main() {
    int fd[2], *status;

    /* Creazione della pipe */
    if (pipe(fd) != 0) {
        fprintf(stdout, "La pipe è fallita.");
        exit(1);
    }

    /* Creazione dei processi figli */
    if (fork() == 0) {
        producer(fd);
    } else {        
        if (fork() == 0)
            consumer(fd);
    }

    wait(status);
    wait(status);

    return 0;
}