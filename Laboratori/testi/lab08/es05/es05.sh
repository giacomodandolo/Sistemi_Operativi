#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage: $0 process interval"
    exit 1
fi

is_zombie=0
flag=1

while [ 1 -eq 1 ]
do
    flag=0
    ps -el | grep $1 > tmp.txt
    while read line
    do
        if [ $? -eq 0 ]
        then 
            pid=$(echo $line | cut -d ' ' -f 5)
            state=$(echo $line | cut -d ' ' -f 2)
                
            # controlla se è un processo zombie
            if [ $state == "Z" ]
            then
                is_zombie=$(($is_zombie+1))
                flag=1
                break
            fi
        fi
        
        echo "is_zombie=$is_zombie"
    done < tmp.txt
    
    # se è stato visto zombie per almeno 5 volte uccidi processo 
    if [ $is_zombie -ge 5 ]
    then
        echo "Process $pid killed"
        kill -9 $pid
        is_zombie=0
    fi

    if [ $flag -eq 0 ]
    then
        exit 0
    fi

    sleep $2
done
