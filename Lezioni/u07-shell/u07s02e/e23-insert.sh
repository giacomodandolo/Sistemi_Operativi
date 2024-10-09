#!/bin/bash

file1="tmp1"
file2="tmp2"
rm -rf $file1 $file2

while : ; do
  echo -n "Stringa (end to stop) "
  read var

  if [ $var = "end" ]; then
    break
  fi

  case $var in
    [abcde]*) echo OK1; echo $var >> $file1;;
    [0-9]*) echo OK2; echo $var >> $file2;;
    *) echo Stringa scartata;;
  esac

done

echo "Vocali"
cat $file1
echo "Cifre"
cat $file2

