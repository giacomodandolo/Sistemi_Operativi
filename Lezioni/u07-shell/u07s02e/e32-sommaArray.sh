#!/bin/bash
# PROBLEMI mostrati:
# parametri su linea di comando
# operazioni aritmetiche
# cicli for di vario tipo
# utilizzo del contenuto delle variabili (da linea di comando e come array)
# array

LIMIT=$#
somma_finale=0
# il -n nell'echo non va a capo
# attenzione alle doppie (( e a LIMIT SENZA $
echo -n "La riga di comando conteneva: "
for ((a=1; a <= LIMIT ; a++)) 
do
   echo -n "${!a} "
   let "somma_finale += ${!a}"
done  
echo

echo "La somma dei valori numerici passati su linea di \
comando e\` $somma_finale."

# la stessa cosa si puo` fare con
echo -n "Ecco gli stessi dati presentati per altra via: "
for a in "$@"
# i parametri su linea di comando vengono cosi` passati uno alla volta
do
   echo -n "$a "
done  
echo

# la stessa cosa si puo` fare con
echo -n "Ecco gli stessi dati presentati per una terza via: "
for a in `echo "$*"`
# attenzione agli accenti gravi che racchiudono il comando
do
   echo -n "$a "
done  
echo

# la stessa cosa si puo` fare con
echo -n "Ecco gli stessi dati presentati per una quarta via: "
for a in $(echo "$*")   
# NOTARE che in $( ) c'e` un comando! (proprio come in ` `)
do
   echo -n "$a "
done  
echo

# per finire usiamo gli array
# attenzione agli \ prima di caratteri "a rischio" (l'accento grave `)
echo -n "Il contenuto dell'array e\`: "
for ((a=1; a <= $# ; a++))
do
   vettore[$a]=${!a}
   echo -n "${vettore[$a]} "
done
echo
