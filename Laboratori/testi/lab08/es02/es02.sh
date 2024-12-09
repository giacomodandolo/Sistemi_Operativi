#!/bin/bash

if test $# -ne 1
then
    echo "Usage: $0 file"
    exit 1
fi

rm tmp.txt

# conta numero di lettere per ogni riga
# e inserisci in tmp.txt
cat $1 | while read line
do
    echo $line | wc -c >> tmp.txt
done

# ordina inversamente per numero di righe
# prendi il primo valore
sort -r -n tmp.txt | head -n 1

# stampa il numero di righe del file
wc -l $1
