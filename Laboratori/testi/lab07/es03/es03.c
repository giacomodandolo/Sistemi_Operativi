#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define DIM 200

typedef struct _threadargs {
    pthread_t thread_id;
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

    pthread_exit((void**) vett);
    return (void*) 0;
}

int main(int argc, char **argv) {
    int i, j, k, n, n_sorted, n_val, *sorted, *vett_int;
    void *vett_void;
    char a[DIM], b[DIM];
    ThreadArgs **ta;
    
    if (argc != 5) {
        fprintf(stdout, "Usage: %s <n> <n_values> <strA> <strB>", argv[0]);
        exit(1);
    }

    n = atoi(argv[1]);
    n_val = atoi(argv[2]);
    strcpy(a, argv[3]);
    strcpy(b, argv[4]);
    
    ta = (ThreadArgs**) malloc(n*sizeof(ThreadArgs*));
    for (i = 0; i < n; i++) {
        ta[i] = (ThreadArgs*) malloc(sizeof(ThreadArgs));
        sprintf(ta[i]->fileIn, "%s%d.txt", a, i+1);
        sprintf(ta[i]->fileOut, "%s", b);

        pthread_create(&(ta[i]->thread_id), NULL, th_task, ta[i]);
    }

    k = 0;
    n_sorted = n*n_val;
    sorted = (int*) malloc(n_sorted*sizeof(int));
    for (i = 0; i < n; i++) {
        pthread_join(ta[i]->thread_id, &vett_void);
        vett_int = (int*) vett_void;
        for (j = 0; j < n_val; j++, k++) {
            sorted[k] = vett_int[j];
        }
        free(vett_int);
    }
    sort(sorted, n_sorted);
    write_file(b, sorted, n_sorted);

    free(sorted);
    for (i = 0; i < n; i++)
        free(ta[i]);
    free(ta);

    return 0;
}