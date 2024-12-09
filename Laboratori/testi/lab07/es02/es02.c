#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define DIM 200

typedef struct _threadargs {
    char fileIn[DIM];
    char fileOut[DIM];
} ThreadArgs;

int* read_file(char *filename, int *n_values) {
    int i, *values;
    FILE* fileIn;
    
    fileIn = fopen(filename, "r");
    fscanf(fileIn, "%d", n_values);
    values = (int*) malloc(*n_values * sizeof(int));
    for(i = 0; i < *n_values; i++)
        fscanf(fileIn, "%d", &values[i]);
    
    fclose(fileIn);
    return values;
}

void sort(int *vett, int n) {
    int i, j, tmp;

    for (i = 0; i < n; i++)
        for (j = 0; j < i; j++)
            if (vett[i] < vett[j]) {
                tmp = vett[i];
                vett[i] = vett[j];
                vett[j] = tmp;
            }

    return;
}

void write_file(char *filename, int *values, int n_values) {
    int i;
    FILE* fileOut;

    fileOut = fopen(filename, "w");
    fprintf(fileOut, "%d\n", n_values);
    for (i = 0; i < n_values; i++)
        fprintf(fileOut, "%d\n", values[i]);

    fclose(fileOut);
    return;
}

void* th_task(void *arg) {
    ThreadArgs *th_args;
    int *vett, n;

    th_args = (ThreadArgs*) arg;
    vett = read_file(th_args->fileIn, &n);
    sort(vett, n);
    write_file(th_args->fileOut, vett, n);

    return;
}

int main(int argc, char **argv) {
    int i, n;
    char a[DIM], b[DIM];
    pthread_t thread_id;
    ThreadArgs *ta;
    
    if (argc != 4) {
        fprintf(stdout, "Usage: %s <n> <strA> <strB>", argv[0]);
        exit(1);
    }

    n = atoi(argv[1]);
    strcpy(a, argv[2]);
    strcpy(b, argv[3]);

    for (i = 0; i < n; i++) {
        ta = (ThreadArgs*) malloc(sizeof(ThreadArgs));
        sprintf(ta->fileIn, "%s%d.txt", a, i+1);
        sprintf(ta->fileOut, "%s%d.txt", b, i+1);

        pthread_create(&thread_id, NULL, th_task, ta);
        pthread_join(thread_id, (void *) 0);
    }

    return 0;
}