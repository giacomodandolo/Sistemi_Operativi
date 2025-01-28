#define N 10

int n_wait[N];
sem_t sync[N]; // inizializzati a 0
sem_t mutex[N]; // inizializzati a 1

void wait_ch(int x) {
    sem_wait(&mutex[x]);
    n_wait[x]++;
    sem_post(&mutex[x]);

    sem_wait(&sync[x]);
}

void signal_ch(int y) {
    sem_wait(&mutex[y]);
    for (int i = 0; i < n_wait[y]; i++)
        sem_post(&sync[y]);
    n_wait[y] = 0;
    sem_post(&mutex[y]);
}

int main() {
    for (int i = 0; i < N; i++) {
        n_wait[i] = 0;
        sem_init(&sync[i], 0, 0);
        sem_init(&mutex[i], 0, 1);
    }
    // ...
}