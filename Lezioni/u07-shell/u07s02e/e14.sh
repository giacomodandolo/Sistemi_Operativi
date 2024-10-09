#!/bin/bash

read file

n=1
while read row
do
  echo "Row=$n $row"
  let n=n+1
done < $1 > $file

exit 0
