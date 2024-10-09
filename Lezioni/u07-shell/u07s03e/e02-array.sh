#!/bin/bash
# Esempio di utilizzo degli array (vettori associativi) in bash

# Vettore classico
echo "Vettore classico"
vett2[3]=pasta
vett2[6]=pane
echo ${vett2[3]}  # Stampa pasta
echo ${#vett2[*]} # Stampa 2
echo ${vett2[*]}  # Stampa pane pasta
echo ${!vett2[*]} # Stampa 1 2



# Vettore associativo
echo "Vettore associativo"
declare -A vett1

vett1[stefano]=3
nome=giulia
vett1[$nome]=pippo

echo ${vett1[stefano]}  # Stampa 3
echo ${vett1["giulia"]} # Stampa pippo
echo ${#vett1[*]}       # Stampa 2
echo ${vett1[*]}        # Stampa pippo 3
echo ${!vett1[*]}       # Stampa giulia stefano

sum=0
for name in ${!vett1[*]}
do
    let sum=${vett1[$name]}+$sum
done
echo "Somma: $sum"

unset vett1
echo ${#vett1[*]} # Stampa 0 (perche' vett1 non esiste piu')

