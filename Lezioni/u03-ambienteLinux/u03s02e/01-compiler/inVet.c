#include "mio.h"

void
inputVet (
  int *vet,
  int *dim
  )
{
  int i;

  fprintf (stdout, "Lettura dimensione (<100): ");
  scanf ("%d", dim);

  fprintf (stdout, "Lettura Vettore:\n");
  for (i=0; i<(*dim); i++) {
    fprintf (stdout, "vet (%d) = ", i);
    scanf ("%d", &vet[i]);
  }

  return;
}
