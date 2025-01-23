#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int pid;

	printf("P1:\tPID = %d\n", getpid());
	pid = fork();

	if (pid == 0) {
		printf("P2:\tPID = %d\t| ", getpid());
		exit(0);
	} else {
		wait(0);
		printf("P3:\tPID = %d\n", getpid());
	}

	pid = fork();

	if (pid == 0) {
		if (fork() == 0)
			printf("P4:\tPID = %d\t| ", getpid());
		else {
			sleep(1);
			printf("P5:\tPID = %d\t| ", getpid());
		}
		exit(0);
	} else {
		wait(0);
		printf("P6:\tPID = %d\n", getpid());
	}
	
	pid = fork();
	
	if (pid == 0) {
		printf("P7:\tPID = %d\t| ", getpid());
		exit(0);
	} else {
		wait(0);
		printf("P8:\tPID = %d\n", getpid());
	}

	printf("P9:\tPID = %d\n", getpid());
	
	return 0;
}
