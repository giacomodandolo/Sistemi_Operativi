#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Uso: ./ex.sh file_name"
	exit 1
fi

if [ ! -e $1 ]
then
	echo "File $1 non trovato."
	exit 1
fi

i=0
j=0
tot=0
while read line
do
	for word in $line
	do
		if [ $i -eq $j ]
		then
			echo $word
			l=$(echo -n $word | wc -m)
			let "tot+=$l"
		fi
		let "j+=1"
	done
	let "j=0"
	let "i+=1"
done < $1

echo "Result: $tot"
