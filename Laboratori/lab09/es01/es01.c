
/* Funzione di incremento atomica */
int atomicIncrement (int *var) {
    int tmp = *var;
    *var = tmp + 1;
    return (tmp);
}

/* Struttura del lock */
typedef struct lock_s {
    int ticketNumber;
    int turnNumber;
} lock_t;

/* Inizializzazione */
void init(lock_t lock) {
    lock.ticketNumber = 0;
    lock.turnNumber = 0;
}

/* Lock */
void lock(lock_t lock) {
    int myTurn = atomicIncrement(&lock.ticketNumber);
    while (lock.turnNumber != myTurn);
}

/* Unlock */
void unlock(lock_t lock) {
    atomicIncrement(&lock.turnNumber);
}
