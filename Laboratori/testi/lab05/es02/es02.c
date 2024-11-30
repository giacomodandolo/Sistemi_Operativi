#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

void exchange(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_info(int *v, int n) {
    int i;
    
    fprintf(stdout, "\tN = %d\n", n);
    fprintf(stdout, "\tVEC = [ ");
    
    for (i = 0; i < n; i++)
        fprintf(stdout, "%d ", v[i]);

    fprintf(stdout, "]\n\n");

}

void print_info_bin(int file_byte, int n) {
    int i, val, c;

    fprintf(stdout, "\tN = %d\n", n);
    fprintf(stdout, "\tVEC = [ ");
    
    for (i = 0; i < n; i++) {
        lseek(file_byte, i*sizeof(int), SEEK_SET);
        c = read(file_byte, &val, sizeof(int));
        if (c <= 0) {
            fprintf(stderr, "Error reading file\n");
            exit(5);
        }
        fprintf(stdout, "%2d ", val);
    }

    fprintf(stdout, "]\n\n");
}

int* bubble_sort_seq(int *v, int n) {
    int i, j;

    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-1-i; j++)
            if (v[j] > v[j+1])
                exchange(&v[j], &v[j+1]);

    return v;
}

void child(int file_byte, int j) {
    int v1, v2, c1, c2;

    /* READ J VALUE FROM ORIGIN OF FILE */
    lseek(file_byte, j*sizeof(int), SEEK_SET);
    c1 = read(file_byte, &v1, sizeof(int));

    /* READ J+1 VALUE FROM ORIGIN OF FILE */
    lseek(file_byte, (j+1)*sizeof(int), SEEK_SET);
    c2 = read(file_byte, &v2, sizeof(int));

    /* IF ERROR, EXIT */
    if (c1 <= 0 || c2 <= 0) {
        fprintf(stderr, "Error reading file\n");
        exit(4);
    }

    /* IF NECESSARY, EXCHANGE */
    if (v1 > v2) {
        lseek(file_byte, j*sizeof(int), SEEK_SET);
        c1 = write(file_byte, &v2, sizeof(int));
        lseek(file_byte, (j+1)*sizeof(int), SEEK_SET);
        c2 = write(file_byte, &v1, sizeof(int));
    }

    return;
}

int* bubble_sort_conc(int *v, int n, int file_byte) {
    int i, j;

    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-1-i; j++)
            if (fork() > 0) {
                // FATHER
                wait((int*) 0);
            } else {
                // CHILD
                child(file_byte, j);
                return 0;
            }
    
    return v;
}

int main(int argc, char **argv) {
    int n, i, *v, *v_seq, file_byte, original_ppid;
    FILE* file;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s filename binary_filename\n", argv[0]);
        exit(1);
    }

    fprintf(stdout, "\n");
    original_ppid = getppid();

    /* READ VALUES */
    file = fopen(argv[1], "r");
    fscanf(file, "%d", &n);
    v = (int*) malloc(n*sizeof(int));
    v_seq = (int*) malloc(n*sizeof(int));
    for (i = 0; i < n; i++) {
        fscanf(file, "%d", &v[i]);
        v_seq[i] = v[i];
    }

    fclose(file);

    /* WRITE BINARY FILE */
    file_byte = creat(argv[2], 0666);
    if (file_byte == -1) {
        fprintf(stderr, "Cannot create file %s\n", argv[1]);
        exit(2);
    }
    for (i = 0; i < n; i++)
        write(file_byte, &v[i], sizeof(int));
    close(file_byte);

    /* PRINT FILE INFO */
    fprintf(stdout, "File infos before sorting (sequential): \n");
    print_info(v, n);

    /* ORDER AND PRINT INFO (SEQUENTIAL) */
    v_seq = bubble_sort_seq(v_seq, n);
    fprintf(stdout, "File infos after sorting (sequential): \n");
    print_info(v_seq, n);

    fprintf(stdout, "------------------------------------------------\n\n");

    /* ORDER AND PRINT INFO (CONCURRENT) */
    file_byte = open(argv[2], 0666);
    if (file_byte == -1) {
        fprintf(stderr, "Cannot open file %s\n", argv[2]);
        exit(3);
    }
    fprintf(stdout, "File infos before sorting (concurrent): \n");
    print_info_bin(file_byte, n);
    bubble_sort_conc(v, n, file_byte);
    if (getppid() != original_ppid)
        exit(0);
    fprintf(stdout, "File infos after sorting (concurrent): \n");
    print_info_bin(file_byte, n);

    fprintf(stdout, "\n"); 
    return 0;
}
