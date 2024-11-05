#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#define MAX_DIM 50

void visualizeR(char* dir) {
    DIR* df = opendir(dir);
    struct dirent *entry;
    struct stat filestat;
    char path[MAX_DIM];

    printf("\n%s:\n", dir);

    while((entry = readdir(df))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        printf("%s\t", entry->d_name);
    }

    printf("\n");
    rewinddir(df);

    while((entry = readdir(df))) {
        if (((int)strcmp(entry->d_name, ".")) == 0 || ((int)strcmp(entry->d_name, "..")) == 0)
            continue;
        
        strcpy(path, dir);

        strcat(strcat(path, "/"), entry->d_name);
        stat(path, &filestat);
        if (S_ISDIR(filestat.st_mode))
            visualizeR(path);
    }
    
    closedir(df);
    return;
}

int main(int argc, char** argv) {
    char* dir = argv[1];

    visualizeR(dir);

    return 0;
}