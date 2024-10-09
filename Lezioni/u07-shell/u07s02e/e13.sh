#!/bin/bash

#for str in foo bar echo charlie tango
#do
#  echo $str
#done

#for foo in 1 2 3 4 5 6 7 8 9 0
#do
#  echo $foo
#done

#num="2 4 6 8 2.3 5.9"
#for file in $num
#do
#  echo $file
#  echo $num
#done

#for i in $(echo {1..50})
#do
#  echo -n "$i " > a.txt
#done
#echo

#n=1
#for i in $* ; do
#  echo "par #" $n = $i
#  let n=n+1
#done

#for file in [ae]* ; do
#  echo $file
#  wc $file
#done

#limit=10
#var=0
#while [ "$var" -lt "$limit" ]
#do
#  echo $var
#  let var=var+1
#done

#echo "Enter"
#read myPass
#while [ "$myPass" != "secret" ]
#do
#  echo "sorry"
#  read myPass
#done

#vet=(2 3 4 5 6 7 8 9 10)
#echo "Size=" ${#vet[*]}
#i=0
#while [ "$i" -lt  ${#vet[*]} ]
#do
#  echo "Element $i: ${vet[$i]}"
#  let i=i+1
#done
#echo ${vet[*]}

#vet=(1 2 5 ciao)
#echo ${vet[0]}
#echo ${vet[1-2]}
#echo ${vet[*]}
#vet[4]=bye
#echo ${vet[*]}
#unset vet[0]
#echo ${vet[*]}
#unset vet
#echo "--" ${vet[*]}

#vet[3]=20
#vet[5]=300
#vet[7]=40
#echo ${vet[*]}
#echo ${#vet[5]}
#echo ${vet[@]}

echo

exit 0
