#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void print_binary(int *binary_number, int n) {
    int i;

    for (i = 0; i < n; i++)
        fprintf(stdout, "%d", binary_number[i]);
    printf("\n");
}

void binary(int *binary_number, int n) {
    int i;

    for (i = 0; i <= n; i++) {
        if (i == n) {
            print_binary(binary_number, n);
            exit(0);
        }

        /* Try 0 */
        binary_number[i] = 0;
        if (fork() > 0) {
            wait((int *) 0);
            /* Try 1 */
            binary_number[i] = 1;
            if (fork() > 0) {
                wait((int *) 0);
                exit(0);
            }
        }
    }

    exit(0);
}

int main(int argc, char **argv) {
    int n, *binary_number;

    n = atoi(argv[1]);
    binary_number = (int*) malloc(n*sizeof(int));
    if (binary_number == NULL) {
        fprintf(stdout, "Errore di allocazione.\n");
        exit(1);
    }

    fprintf(stdout, "Binary numbers:\n");
    binary(binary_number, n);
    free(binary_number);

    return 0;
}