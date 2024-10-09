#!/bin/bash

# Use an array to print-out numbers in reverse order

i=0
while [ 0 ]
do
  echo -n "Element $i: "
  read v
  if [ "$v" -eq "0" ]
  then
    break;
  fi
  
  vet[$i]="$v"
  let i=i+1
done

echo
echo "Number of element: ${#vet[*]}"
echo

let i=i-1
while [ "$i" -ge "0" ]
do
  echo "Element $i: ${vet[$i]}"
  let i=i-1
done
