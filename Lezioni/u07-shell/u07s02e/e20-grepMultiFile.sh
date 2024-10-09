#!/bin/bash

for file in $(ls *.c); do
    #if grep --quiet "POSIX" $file
    grep --quiet "POSIX" $file
    if [ $? -eq 0 ]
      then
        more $file
      fi
done

#Comando alternativo: more $(grep -l POSIX *.c)

exit 0
