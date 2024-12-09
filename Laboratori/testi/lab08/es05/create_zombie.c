#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    if (fork() == 0)
        exit(0);

    sleep(600);

    wait((void *) 0);
    return 0;
}
