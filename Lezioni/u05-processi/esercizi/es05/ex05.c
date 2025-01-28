#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int last_sig = -1;
int count = 0;

void sign_handler(int sig) {
    if (last_sig == sig)
        count++;
    else {
        last_sig = sig;
        count = 1;
    }
    
    if (sig == SIGUSR1) {
        printf("Segnale ricevuto da P1\n");
    }
    else if (sig == SIGUSR2) {
        printf("Segnale ricevuto da P2\n");
    }
}

void P1() {
    while(1) {
        sleep(1);
        kill(getppid(), SIGUSR1);
    }
}

void P2() {
    while(1) {
        sleep(5);
        kill(getppid(), SIGUSR2);
    }
}

int main() {
    char cmd[100];
    int pid1, pid2;

    signal(SIGUSR1, sign_handler);
    signal(SIGUSR2, sign_handler);

    pid1 = fork();
    if (pid1 == 0)
        P1();
    
    pid2 = fork();
    if (pid2 == 0)
        P2();
    
    while(1) {
        pause();
	if (count >= 3) {
            sprintf(cmd, "kill -9 %d", pid1);
            system(cmd);
            sprintf(cmd, "kill -9 %d", pid2);
            system(cmd);
            exit(0);
        }
    }
}
