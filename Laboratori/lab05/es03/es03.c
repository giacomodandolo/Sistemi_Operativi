#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler() {
    return;
}

static void child(pid_t ppid) {
    int n = 2;
    fprintf(stdout, "Child (C) running: PID = %d | FATHER_PID = %d\n", getpid(), ppid);
    
    while(n > 0) {
        pause();
        sleep(1);
        kill(ppid, SIGUSR1);
        fprintf(stdout, "(C) woke up\n");
        n--;
    }
    return;
}

static void father(pid_t pid) {
    int n = 2;
    fprintf(stdout, "Father (F) Running: PID = %d | CHILD_PID = %d\n", getpid(), pid);
    sleep(5);

    while(n > 0) {
        sleep(1);
        kill(pid, SIGUSR1);
        pause();
        fprintf(stdout, "(F) woke up\n");
        n--;
    }
    return;
}

int main() {
    pid_t pid;

    if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Signal Handler Error\n");
        return 1;
    }

    pid = fork();

    if (pid == 0) {
        // CHILD
        child(getppid());
    } else {
        // FATHER
        father(pid);
    }

    return 0;
}
