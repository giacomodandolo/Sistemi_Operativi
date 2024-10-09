#!/bin/bash
# Read a file word-by-word, line-by-line and character-by-character


# word-by-word
for i in $(cat $1) ; do
    echo "WORD: $i"
done
#done > file_out.txt


# line-by-line
while read i ; do
  echo "LINE: $i"
done < $1
#done < $1 > out    #Se volessi redirigerlo sul file out


# character-by-character
while read -n 1 i ; do
      echo "CHAR: $i"
done < $1
