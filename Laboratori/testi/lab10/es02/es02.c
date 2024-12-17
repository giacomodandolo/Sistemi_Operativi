#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

/* Number of threads/monomials */
#define NT 10

/* Description of monomial */
typedef struct monomial_s {
    float c, x;
    int n;
} monomial_t;

/* Necessary thread data */
typedef struct thread_data_s {
    pthread_t th_id;
    int id, n, stop;
    char *name;
    float result;
    sem_t sem;
} thread_data_t;

thread_data_t th[NT+1];

static void *monomial(void* arg) {
    monomial_t m;
    int *id_p, id, file_in;
    int offset, i, j, n;

    id_p = (int*) arg;
    id = *id_p;

    file_in = open(th[id].name, O_RDONLY);
    if (file_in == -1) {
        fprintf(stderr, "Non è stato possibile aprire il file.\n");
        exit(-1);
    }

    i = 0;
    do {
        sem_wait(&th[id].sem);

        /* Calculate offset of file */
        offset = (i*NT + th[id].id - 1) * sizeof(monomial_t);
        i++;
        lseek(file_in, offset, SEEK_SET);
        
        /* 
            If there is a monomial, calculate
            else stop program
        */
        n = read(file_in, &m, sizeof(monomial_t));
        if (n > 0) {
            fprintf(stdout, "th_%2d | %.2f * %.2f ^ %d\n", id, m.c, m.x, m.n);
            th[id].result = m.c;
            for (j = 0; j < m.n; j++) {
                th[id].result = th[id].result * m.x;
            }
            th[id].stop = 0;
        } else {
            th[id].result = 0;
            th[id].stop = 1;
        }

        sem_post(&th[0].sem);
    } while (n > 0);

    close(file_in);
    pthread_exit(0);
}

static void *polynomial(void* arg) {
    int *id_p, id, i, stop;
    float result;

    id_p = (int*) arg;
    id = *id_p;

    do {
        for (i = 0; i < th[id].n; i++)
            sem_wait(&th[id].sem);

        /* Calculate result of polynomial */
        result = 0;
        stop = 0;
        for (i = 1; i <= th[id].n; i++)
            if (th[i].stop == 1)
                stop++;
            else
                result = result + th[i].result;

        if (stop != th[0].n) {
            fprintf(stdout, "th_%2d | Result = %.2f\n", th[id].id, result);
            fprintf(stdout, "---\n");
            for (i = 1; i <= th[0].n; i++) 
                sem_post(&th[i].sem);
        } else {
            pthread_exit(0);
        }
    } while (stop == 0);

    pthread_exit(0);
}

int main(int argc, char **argv) {
    int i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(1);
    }

    setbuf(stdout, 0);

    fprintf(stdout, "---\n");
    /* 
        Thread polynomial
    */
    th[0].id = 0;
    th[0].n = NT;
    th[0].name = NULL;
    th[0].stop = 0;
    th[0].result = 0;
    sem_init(&th[0].sem, 0, 0);
    pthread_create(&(th[0].th_id), NULL, polynomial, (void*) &th[0].id);

    /* 
        Threads monomial
    */
    for (i = 1; i <= NT; i++) {
        th[i].id = i;
        th[i].n = 0;
        th[i].name = argv[1];
        th[i].stop = 0;
        th[i].result = 0;
        sem_init(&th[i].sem, 0, 1);
        pthread_create(&(th[i].th_id), NULL, monomial, (void*) &th[i].id);
    }

    for (i = 0; i <= NT; i++) {
        pthread_join(th[i].th_id, NULL);
    }

    exit(0);
}