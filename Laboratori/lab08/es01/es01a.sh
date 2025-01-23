#!/bin/bash

# se non ci sono 3 argomenti, allora termina
if test $# -ne 3
then
  echo "Usage: $0 directory function file"
  exit 1
fi

# grep -Hnr = 
#   trova le corrispondenze (grep)
#   stampa il nome (H)
#   stampa il numero di riga (n)
#   esegui ricorsivamente (r)

# "$2 *(.*)" $1 =
#   nome della funzione ($2)
#   deve avere dei parametri (*(.*))
#   nome della directory dove cercare ($1)

# sort -t ':' -k 1 -k 2rn
#   ordina (sort)
#   suddividi rispetto a : (-t ':')
#   prendi la prima colonna (-k 1)
#   prendi la seconda colonna, invertila ed è un numero (-k 2rn)

# > $3 
#   inserisci nel file di uscita ($3)

grep -Hnr "$2 *(.*)" $1 | sort -t ':' -k 1,1 -k 2,2n > $3
