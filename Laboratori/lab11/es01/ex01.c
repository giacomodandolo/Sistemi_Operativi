sem_t semAB, semC, semD;
sem_t mutex;

sem_init(semAB, 0, 1);
sem_init(semC, 0, 0);
sem_init(semD, 0, 0);
sem_init(mutex, 0, 1);

void A() {
	sem_wait(semAB);
	sem_wait(mutex);
	// esecuzione
	sem_post(mutex);
	sem_post(semC);
}

void B() {
	sem_wait(semAB);
	sem_wait(mutex);
	// esecuzione
	sem_post(mutex);
	sem_post(semC);
}

void C() {
	sem_wait(semC);
	// esecuzione
	sem_post(semD);
}

void D() {
	sem_wait(semD);
	// esecuzione
	sem_post(semAB);
}