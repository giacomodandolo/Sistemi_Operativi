#include <stdio.h>

int main() {
    int val;
    
    while(val != 0) {
        fscanf(stdin, "%d", &val);
        if (val%2 == 0)
            fprintf(stdout, "Even\t= %d\n", val);
        else
            fprintf(stderr, "Odd\t= %d\n", val);
    } 

    return 0;
}