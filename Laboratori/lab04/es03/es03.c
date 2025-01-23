#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define LEN_FILE 50
#define LEN_COMM 256
#define MAX_ARGS 15

int main(int argc, char** argv) {
    if (argc < 2)
        return 1;
   
    int n, i;
    char buf[LEN_COMM], comm[LEN_COMM], **args, *tmp;
    FILE* file = fopen(argv[1], "r");

    printf("--- System ---\n");
    comm[0] = '\0';    
    while(fscanf(file, "%s", buf) != EOF) {
        if (strcmp(buf, "end") != 0) {
            strcat(comm, buf);
            strcat(comm, " ");
        } else {
            printf("Comando: %s\n", comm);
            system(comm);
            comm[0] = '\0';
            printf("\n");
        }
    }
    fclose(file);

    printf("--- Exec ---\n");
    file = fopen(argv[1], "r");
    n = 0;
    args = (char**) malloc(MAX_ARGS * sizeof(char*));
    for (i = 0; i < MAX_ARGS; i++)
        args[i] = (char*) malloc(LEN_COMM * sizeof(char));

    while(fscanf(file, "%s", buf) != EOF) {
        if (strcmp(buf, "end") != 0) {
            strcpy(args[n], buf);
            n++;
        } else {
            printf("Comando: ");
            for (i = 0; i < n; i++) {
                printf("%s ", args[i]);
            }
            printf("\n");

            tmp = args[n];
            args[n] = NULL;
            if (fork() == 0) {
                printf("PPID = %d | PID = %d\n", getppid(), getpid());
                execvp(args[0], args);
            } else
                sleep(3);
            args[n] = tmp;
            n = 0;
            printf("\n");
        }
    }
    fclose(file);

    return 0;
}
