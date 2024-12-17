#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef int *semaphore_pipe_t;

semaphore_pipe_t semA, semBCD, semEF, semG, semH, semI;

semaphore_pipe_t init_sem() {
    int *sem;
    sem = calloc(2, sizeof(int));
    pipe(sem);
    return sem;
}

void wait_sem(semaphore_pipe_t s) {
    int j;
    if (read(s[0], &j, 1) <= 0) {
        fprintf(stderr, "Error: signal\n");
        exit(1);
    }
}

void signal_sem(semaphore_pipe_t s) {
    if (write(s[1], "x", 1) <= 0) {
        fprintf(stderr, "Error: signal\n");
        exit(1);
    }
}

void pA() {
    wait_sem(semA);
    sleep(1);
    printf("\nA\n");
    signal_sem(semBCD);
    signal_sem(semBCD);
    signal_sem(semBCD);
    exit(0);
}

void pB() {
    wait_sem(semBCD);
    sleep(2);
    printf("B ");
    signal_sem(semI);
    exit(0);
}

void pC() {
    wait_sem(semBCD);
    sleep(3);
    printf("C ");
    signal_sem(semEF);
    signal_sem(semEF);
    exit(0);
}

void pD() {
    wait_sem(semBCD);
    sleep(4);
    printf("D\n");
    signal_sem(semH);
    exit(0);
}

void pE() {
    wait_sem(semEF);
    sleep(3);
    printf("E ");
    signal_sem(semG);
    exit(0);
}

void pF() {
    wait_sem(semEF);
    sleep(4);
    printf("F\n");
    signal_sem(semG);
    exit(0);
}

void pG() {
    wait_sem(semG);
    wait_sem(semG);
    sleep(1);
    printf("G ");
    signal_sem(semI);
    exit(0);
}

void pH() {
    wait_sem(semH);
    sleep(7);
    printf("H\n");
    signal_sem(semI);
    exit(0);
}

void pI() {
    wait_sem(semI);
    wait_sem(semI);
    wait_sem(semI);
    sleep(1);
    printf("I\n");
    signal_sem(semA);
}

int main() {
    semA = init_sem();
    semBCD = init_sem();
    semEF = init_sem();
    semG = init_sem();
    semH = init_sem();
    semI = init_sem();
    
    signal_sem(semA);

    while (1) {
        if (fork() != 0) { /* ABCDEFGHI */
            if (fork() != 0) { /* BCDEFGHI */
                if (fork() != 0) { /* DHI */
                    if (fork() != 0) { /* HI */
                        if (fork() != 0)
                            pI();
                        else
                            pH();
                    } else { /* D */
                        pD();
                    }
                } else { /* CEFG */
                    if (fork() != 0) { /* C */
                        pC();
                    } else { /* EFG */
                        if (fork() != 0) { /* E */
                            pE();
                        } else { /* FG */
                            if (fork() != 0)
                                pF();
                            else
                                pG();
                        }
                    }
                }
            } else { /* B */
                pB();
            }
        } else { /* A */
            pA();
        }
    }

    return 0;
}