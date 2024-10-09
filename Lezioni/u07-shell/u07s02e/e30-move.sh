#!/bin/bash

case $# in
  0|1) echo Usage: movetodir dir file1 file2 ... filen ; exit 1;;
esac

if test ! -d $1
then
  echo "Create Directory $1"
  mkdir $1
fi

for i in $* ; do
  if test $i != $1 ; then
    echo -n "$i in $1 (y/n)? "
    read risposta
    if [ $risposta = "y" ] ; then
      if cp $i $1
        then echo si $1/$i
        else echo Error for $1
      fi
    fi
 fi
done

