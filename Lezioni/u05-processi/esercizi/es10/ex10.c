#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define N 100

int main() {
	int fd[2];
	char line[N];
	
	pipe(fd); // 0 = read, 1 = write

	if (fork()) { // scrittore
		close(fd[0]);
		while(1) {
			scanf("%s", line);
			write(fd[1], line, (strlen(line)+1)*sizeof(char));
		}
	} else { // lettore
		close(fd[1]);
		while(1) {
			read(fd[0], line, N*sizeof(char));
			printf("%s\n", line);
		}
	}
	return 0;
}
