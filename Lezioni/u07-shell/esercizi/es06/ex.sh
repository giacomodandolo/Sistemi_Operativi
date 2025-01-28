#!/bin/bash

ps -aux | tail -n 3 > tmp.txt

while read line
do
	user=$(echo $line | tr -s " " | cut -d " " -f 1)
	pid=$(echo $line | tr -s " " | cut -d " " -f 2)
	mem=$(echo $line | tr -s " " | cut -d " " -f 4 | cut -d "." -f 1)

	if [ $user != "root" ] && [ $mem -ge 25 ]
	then
		kill -9 $pid
	fi
done < tmp.txt

rm tmp.txt
