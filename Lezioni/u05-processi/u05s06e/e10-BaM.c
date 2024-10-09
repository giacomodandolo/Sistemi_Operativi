// Passaggio di dati tra due processi tramite una pipe
// test con le signal sul kernel Linux
// SI NOTI CHE DI FATTO LA SIGNAL con kernel Fedora ha lo stesso
// comportamento della sigaction() !!!

#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
void catchSIGUSR1(int sig);
void catchSIGUSR2(int sig);

//****************************************************************************
int fd[2];

//****************************************************************************
int father(int child){
	int f,len,status;
	char buf[512]; 	// dim del blocco base (file grande)

        // debug
	signal(SIGUSR1,&catchSIGUSR1);
        // 29 e' il numero di riga (ovviamente provvisorio)
        printf("Processo padre SIGUSR1: %d (riga 29).\n", getpid());
        pause();  //pause per il debug

        // due pause() poste solo per poter fare esperimenti
        // facendo kill -USR1 da un'altra shell
        // pause();
        // pause();

	close(fd[0]); 		//chiusura lettura
	if((f=open("in.txt",O_RDONLY))==-1) printf("Errore in apertura file!\n");
	else{
		while((len=read(f,buf,1))!=0){
			write(fd[1],buf,len);
		}
	 	close(f);
	}
	//kill(child,SIGUSR1);
	close(fd[1]);
 	//se commento la riga precedente, il processo padre aspetta il figlio ma il figlio
	//si aspetta ancora dati da leggere 
	wait(&status);
	return 0;
}

//****************************************************************************

void catchSIGUSR1(int sig){
        /* metto la signal subito all'inizio per minimizzare la
           race condition in base alla quale una nuova chiamata 
           dovuta all'arrivo di un nuovo segnale termina il processo
           (condizione di default per questo segnale) in assenza del
           rinnovo tempestivo del gestore; in realta' cio' sotto LINUX
           NON avviene (vedere dopo) */
	//signal(SIGUSR1,&catchSIGUSR1); -> NON NECESSARIO
	signal(SIGUSR2,&catchSIGUSR2); //commentato per ora
        printf("Sono %d. Ho ricevuto il segnale SIGUSR1.\n", getpid());
        /* lasciando la pause alla riga dopo si ha che:
           - SIGUSR1 viene per ora bloccato e non gestito fino alla fine
             della routine; infatti come da pagina di manuale man signal
  Upon  arrival of a signal with number signum the following happens.  If
  the corresponding handler  is  set  to  SIG_IGN,  then  the  signal  is
  ignored.   If  the  handler  is set to SIG_DFL, then the default action
  associated to the signal (see signal(7)) occurs.  Finally, if the  han-
  dler  is  set to a function sighandler then first either the handler is
  reset to SIG_DFL or an implementation-dependent blocking of the  signal
  is performed and next sighandler is called with argument signum.
  The original Unix signal() would reset the handler to SIG_DFL, and Sys-
  tem  V  (and the Linux kernel and libc4,5) does the same.  On the other
  hand, BSD does not reset the handler, but blocks new instances of  this
  signal from occurring during a call of the handler.  The glibc2 library
  follows the BSD behaviour.
             NOTARE che il nuovo segnale viene accodato, ma non piu'
             di un segnale viene posto in coda; non e' neanche necessario
             rifare la signal -> provare
           - di fatto non vi e' modo di uscire, perche' un altro segnale
             (ad es. SIGUSR2) andrebbe gestito (cosa che si potrebbe fare
             inserendo il gestore commentato -> in tal modo pero'
             si arriverebbe al punto in cui ne' USR1 ne' USR2 vengono
             piu' riconosciuti, e ci vorrebbe un terzo segnale, etc..,
             il problema naturalmente e' la pause() )e qui non e' stato settato
             il gestore; l'arrivo di tale segnale non gestito
             produce la fine del processo; insomma la pause() che
	     segue VA commentata sotto Linux, altrimenti il programma
	     vi si ferma sopra (il segnale USR1 la potrebbe sbloccare,
	     ma viene accodato perche' si e` nel gestore, e un altro
	     segnale (es. USR2) provocherebbe la fine immediata
	     del programma, non essendo USR2 gestito) */
        /* in altri termini se non uso il debug e metto la pause nella riga
        successiva (e aggiungo anche il gestore si USR2) per uscire devo
        madare: USR1 al padre, USR2 al padre e poi USR2 al figlio
        in modo tale da far terminare il processo */
        pause(); printf("Sono %d. Ho superato la pause()\n", getpid());
        //sleep(10);
}
void catchSIGUSR2(int sig){
	signal(SIGUSR2,&catchSIGUSR2);
        printf("Sono %d. Ho ricevuto il segnale SIGUSR2.\n", getpid());
        // pause();
}

int child(){

	int len;
	char buf[512]; 	// dim del blocco base (file grande)

        // debug
	signal(SIGUSR2,&catchSIGUSR2);
        // 117 e' il numero di riga (ovviamente provvisorio)
        printf("Processo figlio SIGUSR2: %d (riga 117).\n", getpid());
        pause();  //pause per il debug

	close(fd[1]);  //chiusura scrittura
	printf("Inizio lettura...\n\n");
	while((len=read(fd[0],buf,1))!=0){
		write(1,buf,len);
	}
	printf("...fine lettura!\n");
	return 0;
}

//****************************************************************************
int main (void){

	int pid;
	if(pipe(fd)==-1){
		printf("Pipe Error!\n");
		return 1;
	}

	switch ((pid=fork())){

		case -1:  //errore nella fork
			fprintf(stderr,"Fork Error\n");
			return 1;

		case 0 : //processo figlio
			child();
			printf("Fine del processo %d\n",getpid());
			return 0;
	}

	father(pid);
  	printf("Fine del processo padre %d\n",getpid());
	return 0;
}
