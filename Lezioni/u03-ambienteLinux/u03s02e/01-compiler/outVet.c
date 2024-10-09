#include "mio.h"

void
outputVet (
  int *vet,
  int dim
  )
{
  int i;

  fprintf (stdout, "Visualizzazione Vettore:\n");
  for (i=0; i<dim; i++) {
    fprintf (stdout, "vet (%d) = %d\n", i, vet[i]);
  }

  return;
}