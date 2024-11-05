#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define MAX_DIM 1024

void copyR(char* source, char* dest) {
    DIR* ds = opendir(source);
    struct dirent *entry;
    struct stat filestat;
    int fs, fd, n_read;
    char new_source[MAX_DIM], new_dest[MAX_DIM], buf[MAX_DIM];
    
    while((entry = readdir(ds))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        strcpy(new_source, source);
        strcpy(new_dest, dest);

        strcat(strcat(new_source, "/"), entry->d_name);
        strcat(strcat(new_dest, "/"), new_source);
        
        stat(new_source, &filestat);
        if (S_ISDIR(filestat.st_mode)) {
            mkdir(new_dest, S_IRWXU | S_IRWXG | S_IRWXO);
        }
        else {
            fs = open(new_source, O_RDONLY);
            fd = open(new_dest, O_WRONLY | O_CREAT, 0770);
            
            while((n_read = read(fs, buf, MAX_DIM)) > 0)
                write(fd, buf, n_read);
            
            close(fs);
            close(fd);
        }

        printf("Copied %s -> %s\n", new_source, new_dest);
    }

    printf("\n");
    rewinddir(ds);

    while((entry = readdir(ds))) {
        if (((int)strcmp(entry->d_name, ".")) == 0 || ((int)strcmp(entry->d_name, "..")) == 0)
            continue;
        
        strcpy(new_source, source);
        strcpy(new_dest, dest);

        strcat(strcat(new_source, "/"), entry->d_name);
        stat(new_source, &filestat);
        if (S_ISDIR(filestat.st_mode))
            copyR(new_source, dest);
    }
    
    closedir(ds);
    return;
}

void copy(char* source, char* dest) {
    char new_dest[MAX_DIM];
    
    strcpy(new_dest, dest);
    strcat(strcat(new_dest, "/"), source);
    mkdir(new_dest, S_IRWXU | S_IRWXG | S_IRWXO);
    printf("Copied %s -> %s\n", source, new_dest);

    copyR(source, dest);
}

int main(int argc, char** argv) {
    char* source = argv[1];
    char* dest = argv[2];

    copy(source, dest);

    return 0;
}