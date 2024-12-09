#!/bin/bash

if [ $# -ne 1 ] 
then
    echo -n "File Name: "
    read nFile
else
    nFile=$1
fi

h=0
for word in $(cat $nFile)
do
    flag=0

    for((i=0; i<${#word_array[*]}; i++))
    do
        if [ $word = ${word_array[$i]} ]
        then
            freq_array[$i]=$((freq_array[$i]+1))
            flag=1
        fi
    done

    if [ $flag -eq 0 ]
    then
        word_array[$h]=$word
        freq_array[$h]=1
        h=$(($h+1))
    fi

done

for((i=0; i<${#word_array[*]}; i++))
do
    echo ${word_array[$i]} "-" ${freq_array[$i]}
done

