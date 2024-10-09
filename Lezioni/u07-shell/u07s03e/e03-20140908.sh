#!/bin/bash

# Controllo che il numero di parametri siano corretti (deve esserci almento un parametro 
if [ $# -eq 0 ]
then
   echo "Utilizzo: $0 <lista_di_direttori>"
   exit 1
fi

# Controllo che tutti i parametri siano dei direttori
for i in $*
do
    if [ ! -d $i ]
    then
        echo "$i non e' un direttorio"
        exit 2
    fi
done


for dir in $* # Ciclo su tutti i direttori
do

    ls -la $dir > .tmp_$$ # Output di ls -al nel file nascosto .tmp_$$
    while read line #Ciclo su tutte le linee del file
    do
        f1=$(echo $line | cut -d " " -f 1) # Estraggo la prima colonna
        # Caso directory
        # Si fa notare che il comando grep se fa il match almeno di un'espressione regolare fa una exit 0 (settando il valore di $?, valori di ritorno dell'ultimo comando, a 0), altrimenti $? e' uguale a 1 
        r1=$(echo $f1 | grep "^d") > /dev/null
        if [ $? -eq 0 ]
        then
            dname=$(echo $line | cut -d " " -f 9)
            nsubdirs=$(find $dname -type d | wc -l)
            echo $dname is a directory having $nsubdirs subdirs
        fi

        # Caso file
        echo $f1 | grep "^-" > /dev/null
        if [ $? -eq 0 ]
        then
            name=$(echo $line | cut -d " " -f 9)
            owner=$(echo $line | cut -d " " -f 3)
            size=$(echo $line | cut -d " " -f 5)
            echo $name is a regular file, its owner is $owner and its size is $size bytes
        fi

        # Caso link simbolico
        echo $f1 | grep "^l" > /dev/null
        if [ $? -eq 0 ]
        then
            name=$(echo $line | cut -d " " -f 9)
            date=$(echo $line | cut -d " " -f 6,7,8)
            reference=$(echo $line | cut -d " " -f 11)
            echo $name is a link created on $date, it refers to $reference
        fi
    done < .tmp_$$
done

rm .tmp_$$

exit 0
