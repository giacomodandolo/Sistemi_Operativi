#!/bin/bash

longest_word=""
longest_length=0

for word in $(cat file.txt)
do
	length=$(echo $word | wc -m)
	if [ $length -gt $longest_length ] 
	then 
		longest_length=$length
		longest_word=$word
	fi
done
echo $longest_word
