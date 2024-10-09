#!/bin/bash

val="0"
avg="0"
sum="0"
num="0"

while true; do

  echo -n "Value ]0-100[: ";
  read val;

  if [ $val -le 0 -o $val -ge 100 ]; then
    echo "Average: $avg."
    break
  else
    sum=$[$sum + $val]
    num=$[$num + 1]
    avg=$[$sum / $num]
  fi
done

exit 0
