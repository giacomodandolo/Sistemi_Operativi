#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int fp, fd;
	char *buf;

	fp = open(argv[1], O_RDONLY);
	fd = open(argv[2], O_WRONLY|O_CREAT, 0666);
	while(read(fp, buf, 1) > 0) 
		write(fd, buf, 1);

	close(fp);
	close(fd);

	return 0;
}
