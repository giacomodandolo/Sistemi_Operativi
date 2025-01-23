#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semA, semBCD, semEF, semG, semH, semI;
pthread_t tid_A, tid_B, tid_C, tid_D, tid_E, tid_F, tid_G, tid_H, tid_I;

void* process_A(void *arg) {
    while(1) {
        sem_wait(&semA);
        printf("\nA\n");
        sleep(2);
        sem_post(&semBCD);
        sem_post(&semBCD);
        sem_post(&semBCD);
    }
}

void* process_B(void *arg) {
    while(1) {
        sem_wait(&semBCD);
        printf("B\n");
        sleep(2);
        sem_post(&semI);
    }
}

void* process_C(void *arg) {
    while(1) {
        sem_wait(&semBCD);
        printf("C\n");
        sleep(2);
        sem_post(&semEF);
        sem_post(&semEF);
    }
}

void* process_D(void *arg) {
    while(1) {
        sem_wait(&semBCD);
        printf("D\n");
        sleep(2);
        sem_post(&semH);
    }
}

void* process_E(void *arg) {
    while(1) {
        sem_wait(&semEF);
        printf("E\n");
        sleep(2);
        sem_post(&semG);
    }
}

void* process_F(void *arg) {
    while(1) {
        sem_wait(&semEF);
        printf("F\n");
        sleep(2);
        sem_post(&semG);
    }
}

void* process_G(void *arg) {
    while(1) {
        sem_wait(&semG);
        sem_wait(&semG);
        printf("G\n");
        sleep(2);
        sem_post(&semI);
    }
}

void* process_H(void *arg) {
    while(1) {
        sem_wait(&semH);
        printf("H\n");
        sleep(2);
        sem_post(&semI);
    }
}

void* process_I(void *arg) {
    while(1) {
        sem_wait(&semI);
        sem_wait(&semI);
        sem_wait(&semI);
        printf("I\n");
        sleep(2);
        sem_post(&semA);
    }
}

int main() {
    sem_init(&semA, 0, 1);
    sem_init(&semBCD, 0, 0);
    sem_init(&semEF, 0, 0);
    sem_init(&semG, 0, 0);
    sem_init(&semH, 0, 0);
    sem_init(&semI, 0, 0);

    pthread_create(&tid_A, NULL, process_A, NULL);
    pthread_create(&tid_B, NULL, process_B, NULL);
    pthread_create(&tid_C, NULL, process_C, NULL);
    pthread_create(&tid_D, NULL, process_D, NULL);
    pthread_create(&tid_E, NULL, process_E, NULL);
    pthread_create(&tid_F, NULL, process_F, NULL);
    pthread_create(&tid_G, NULL, process_G, NULL);
    pthread_create(&tid_H, NULL, process_H, NULL);
    process_I(NULL);

    sem_destroy(&semA);
    sem_destroy(&semBCD);
    sem_destroy(&semEF);
    sem_destroy(&semG);
    sem_destroy(&semH);
    sem_destroy(&semI);

    return 0;
}