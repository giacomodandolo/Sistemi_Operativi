#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
    int i, j, new, max_files, max_n, max_value;
    char current[256];
    FILE* file;

    max_files = atoi(argv[1]);
    max_n = atoi(argv[2]);
    max_value = atoi(argv[3]);

    for (i = 0; i < max_files; i++) {
        sprintf(current , "%s%d.txt", "a", i+1);
        file = fopen(current, "w");
        fprintf(file, "%d\n", max_n);
        for (j = 0; j < max_n; j++) {
            new = rand()%max_value;
            fprintf(file, "%d\n", new);
        }
        fclose(file);
    }

    return 0;
}