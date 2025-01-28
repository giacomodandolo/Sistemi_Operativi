#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Errore"
	exit
fi

while read line
do
	n=$(echo $line | wc -w)
	if [ $[$n%2] -eq 1 ]
	then
		echo $line | tr [A-Z] [a-z]
	else
		echo $line | tr [a-z] [A-Z]
	fi
done < $1
