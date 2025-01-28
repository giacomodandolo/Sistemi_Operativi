#!/bin/bash

if [ $# -ne 2 ]
then
	echo "Usage: $0 <nome_utente> <nome_direttorio>"
	exit 0
fi

for file in $(find $2 -user $1 -type f)
do
	# controlla se il file contiene la stringa ***Da Modificare
	egrep -e "^\*\*\*Da Modificare" $file
	
	# se la contiene, esegui le modifiche richieste
	if [ $? -eq 0 ]
	then
		grep -v "^\*\*\*DaModificare" $file > tmp.txt
		mv tmp.txt $file" _mod"
		rm -f $file
	fi
done