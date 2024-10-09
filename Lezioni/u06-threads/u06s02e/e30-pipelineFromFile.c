/*
 * Thread in pipeline
 * T1: get
 * T2: update
 * T3: print
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "pthread.h"

char next, this, last; 
FILE * fg;

static void *
GET (void *arg) {
  char *c = (char *) arg;

  *c = fgetc (fg);

  return  NULL;
}

static void *
UPDATE (void *arg) {
  char *c = (char *) arg;
 
  *c = toupper( *c );
   
  return  NULL;
}

static void *
PRINT (void *arg) {
  char *c = (char *) arg;

  putchar (*c);
 
  return  NULL;
}

int
main (
  int argc,
  char ** argv
  )
{
  int retcode;
  pthread_t t_get, t_update, t_print;
  void *retval;
   
  if ((fg = fopen(argv[1], "r")) == NULL){
    perror ("Errore fopen\n");
    exit (0);
  }
  this = ' ';
  last = ' ';
  next = ' ';
  while (next != EOF) {
    retcode = pthread_create (&t_get, NULL, GET, &next);
    if (retcode != 0)
      fprintf (stderr, "create GET failed %d\n", retcode);
       
    retcode = pthread_create (&t_update, NULL, UPDATE, &this);
    if (retcode != 0)
      fprintf (stderr, "create UPDATE failed %d\n", retcode);

    retcode = pthread_create (&t_print, NULL, PRINT, &last);
    if (retcode != 0)
      fprintf (stderr, "create PRINT failed %d\n", retcode);   
    
    retcode = pthread_join (t_get, &retval); 
    if (retcode != 0)
      fprintf (stderr, "join GET failed %d\n", retcode);
    
    retcode = pthread_join (t_update, &retval);     
    if (retcode != 0)
      fprintf (stderr, "join UPDATE failed %d\n", retcode);
    
    retcode = pthread_join (t_print, &retval);     
    if (retcode != 0)
      fprintf (stderr, "join PRINT failed %d\n", retcode);
    
    last = this;
    this = next;
  }
  
  // Last two chars processing
  
  retcode = pthread_create (&t_update, NULL, UPDATE, &this);
  if (retcode != 0)
    fprintf (stderr, "create UPDATE failed %d\n", retcode);

  retcode = pthread_create (&t_print, NULL, PRINT, &last);
  if (retcode != 0)
    fprintf (stderr, "create PRINT failed %d\n", retcode);   
    
  retcode = pthread_join (t_update, &retval);     
  if (retcode != 0)
    fprintf (stderr, "join UPDATE failed %d\n", retcode);
    
  retcode = pthread_join (t_print, &retval);     
  if (retcode != 0)
    fprintf (stderr, "join PRINT failed %d\n", retcode);
      
  retcode = pthread_create (&t_print, NULL, PRINT, &this);
  if (retcode != 0)
    fprintf (stderr, "create PRINT failed %d\n", retcode);
    
  return 0;
}
