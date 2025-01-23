#include <stdio.h>

int main(int argc, char **argv) {
	FILE *fs, *fd;
	char c;
	char name[1024];
	
	// inserisce dentro name il secondo argomento
	sprintf(name, "%s.1", argv[2]);
	fs = fopen(argv[1], "r");
	fd = fopen(name, "w");
	while (fscanf(fs, "%c", &c) != EOF) {
		fprintf(fd, "%c", c);
	}
	fclose(fs);
	fclose(fd);
	
	return 0;
}
