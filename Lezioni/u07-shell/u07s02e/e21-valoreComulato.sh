#!/bin/bash
numero=0
for x in `cat $1`
do
  numero=$[$numero+$x]
  echo $numero
done
