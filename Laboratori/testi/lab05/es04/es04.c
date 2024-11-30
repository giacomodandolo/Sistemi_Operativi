#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define N 1024
#define FILENAME "message.txt"

static void signal_handler() {
    return;
}

void consumer() {
    FILE* file;
    char line[N];
    int receivedMsg = 0, consumerPID, producerPID, i;

    consumerPID = getpid();

    while(1) {
        /* WAITS FOR PRODUCER TO PRODUCE */
        pause();

        /* OBTAINS DATA FROM SHARED FILE */
        file = fopen(FILENAME, "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file: %s\n", FILENAME);
            exit(2);
        }
        fscanf(file, "%d %s", &producerPID, line);
        fclose(file);
        fflush(stdout);

        if (strcmp(line, "end") == 0)
            break;

        /* STRING TO UPPERCASE */
        for (i = 0; i < strlen(line); i++)
            line[i] = toupper(line[i]);

        /* CONSUMES DATA */
        fprintf(stdout, "CONSUMED (consumerPID = %d): %s\n", consumerPID, line);
        fflush(stdout);
        sleep(1);

        /* SENDS SIGNAL TO PRODUCER */
        receivedMsg++;
        kill(producerPID, SIGUSR1);
    }

    exit(receivedMsg);
}

void producer(pid_t consumerPID) {
    FILE* file;
    char line[N];
    int sentMsg = 0, producerPID;

    producerPID = getpid();

    while(1) {
        /* PRODUCES DATA */
        fprintf(stdout, "PRODUCED (producerPID = %d): ", producerPID);
        scanf("%s", line);
        fflush(stdout);

        /* INSERTS DATA INTO SHARED FILE */
        file = fopen(FILENAME, "w");
        if (file == NULL) {
            fprintf(stderr, "Error opening file: %s\n", FILENAME);
            exit(2);
        }
        fprintf(file, "%d %s", producerPID, line);
        fclose(file);

        /* SENDS SIGNAL TO CONSUMER */
        sentMsg++;
        kill(consumerPID, SIGUSR1);
        if (strcmp(line, "end") == 0)
            break;
        
        /* WAITS FOR CONSUMER TO FINISH */
        pause();
    }

    exit(sentMsg);
}

int main() {
    int status, cpid;
    int producerPID, consumerPID;

    signal(SIGUSR1, signal_handler);

    consumerPID = fork();
    if (consumerPID == 0) {
        consumer();
    } else {
        producerPID = fork();
        if (producerPID == 0)
            producer(consumerPID);
    }

    fprintf(stdout, "PRODUCER PID %d\n", producerPID);
    fprintf(stdout, "CONSUMER PID %d\n", consumerPID);

    /* 
        WAITS FOR THE END OF THE TWO PROCESSES

        Necessario per l'esecuzione corretta del codice,
        poiché altrimenti il produttore continua a "produrre"
        lo stesso valore, e il consumatore continua a "consumare"
        lo stesso valore all'infinito.
        Ciò accade perché l'acquisizione dei dati avviene
        da terminale attraverso la digitazione su tastiera, ed 
        essendo terminato il processo padre la riga di comando 
        è riconsegnata all'utente, portando ad un'esecuzione
        scorretta dei processi produttore e consumatore. 
    */
    waitpid(consumerPID, &status, 0);
    waitpid(producerPID, &status, 0);

    return 0;
}