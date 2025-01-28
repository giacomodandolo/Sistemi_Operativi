
sem_t s1, s2, s3, d;

init(s1, 0, 1); // processo 1
init(s2, 0, 0); // processo 2
init(s3, 0, 0); // processo 3
init(d, 0, 0); // per gestire il segnale P2 -> P3
int n = 0;

void P1() {
    while(1) {
        wait(s1);
        // SC
        signal(s2);
    }
}

void P2() {
    while(1) {
        wait(s2);
        n++;
        if (n == 1)
            signal(s2);
        else {
            n = 0;
            signal(d);
            signal(d);
        }
        wait(d);
        // SC
        signal(s3);
    }
}

void P3() {
    while(1) {
        wait(s3);
        wait(s3);
        // SC
        signal(s1);
    }
}

