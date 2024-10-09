#!/bin/bash

sum=0
cont=$1
while [ $cont -le $2 ]
do
  sum=$[$sum + 3 * $cont * $cont * $cont]
  sum=$[$sum + 2 * $cont * $cont]
  sum=$[$sum - 12]
  cont=$[$cont+1]
done

echo "Sum (f=3x^3+2x^2-12) in "$1" "$2" e\` "$sum"."
