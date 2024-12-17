#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

#define L 100+1+1

sem_t sem_read, sem_convert, sem_write;
FILE *file_in, *file_out;
char line[L];

static void *read_file(void* arg) {
    fprintf(stdout, "Reading thread started...\n");

    do {
        sleep(1);
        sem_wait(&sem_read);
        if (fgets(line, L, file_in) == NULL) {
            strcpy(line, "");
            sem_post(&sem_convert);
            break;
        }
        strtok(line, "\n");
        fprintf(stdout, "\nReading = %s\n", line);
        sem_post(&sem_convert);
    } while (1);

    fprintf(stdout, "Reading thread ended.\n");
    pthread_exit((void*) 1);
}

static void *convert_line(void* arg) {
    int i, len;
    char tmp;
    fprintf(stdout, "Convert thread started...\n");

    do {
        sem_wait(&sem_convert);
        if (strcmp(line, "") == 0) {
            sem_post(&sem_write);
            break;
        }
        fprintf(stdout, "Converting = %s\n", line);
        len = strlen(line) - 1;
        for (i = 0; i < len; i++) {
            line[i] = toupper(line[i]);
        }

        for (i = 0; i < ((int) ((len-1)/2)); i++) {
            tmp = line[i];
            line[i] = line[len-i-1];
            line[len-i-1] = tmp;
        }

        sem_post(&sem_write);
    } while (1);

    fprintf(stdout, "Convert thread ended.\n");
    pthread_exit((void*) 1);
}

static void *write_file(void* arg) {
    fprintf(stdout, "Writing thread started...\n");

    do {
        sem_wait(&sem_write);
        if (strcmp(line, "") == 0) {
            break;
        }
        fprintf(stdout, "Writing = %s\n", line);
        fprintf(file_out, "%s", line);
        sem_post(&sem_read);
    } while (1);

    fprintf(stdout, "Writing thread ended.\n");
    pthread_exit((void*) 1);
}

int main(int argc, char** argv) {
    pthread_t th_read, th_convert, th_write;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file_in> <file_out>", argv[0]);
        exit(1);
    }

    file_in = fopen(argv[1], "r");
    file_out = fopen(argv[2], "w");
    if (file_in == NULL || file_out == NULL) {
        fprintf(stderr, "Error opening files.\n");
        exit(2);
    }

    sem_init(&sem_read, 0, 1);
    sem_init(&sem_convert, 0, 0);
    sem_init(&sem_write, 0, 0);

    pthread_create(&th_read, NULL, read_file, NULL);
    pthread_create(&th_convert, NULL, convert_line, NULL);
    pthread_create(&th_write, NULL, write_file, NULL);

    pthread_join(th_read, NULL);
    pthread_join(th_convert, NULL);
    pthread_join(th_write, NULL);

    fclose(file_in);
    fclose(file_out);

    exit(0);
}
