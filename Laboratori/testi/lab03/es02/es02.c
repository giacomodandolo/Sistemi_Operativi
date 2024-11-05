#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int i, n = strtol(argv[1], NULL, 10), t = strtol(argv[2], NULL, 10), pid;

	for (i = 0; i < n; i++) {
		if ((pid = fork()) > 0) { // se padre, crea altro figlio
			pid = fork();
			if (pid > 0)
				return 0;
		}
		printf("i = %d : PPID = %d\t| PID = %d\n", i, getppid(), getpid());
	}

	if (pid == 0) {
		sleep(t);
		printf("PID = %d\t| Terminato!\n", getpid());
	}

	return 0;
}
