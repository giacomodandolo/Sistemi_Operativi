
sem_t a, b;

sem_init(a, 0, 0);
sem_init(b, 0, 0);

void funz_a() {
    sem_signal(b);
    sem_wait(a);
    // esecuzione
}

void funz_b() {
    sem_signal(a);
    sem_wait(b);
    // esecuzione
}