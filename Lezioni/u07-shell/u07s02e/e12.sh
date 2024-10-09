#!/bin/bash

echo -n "Is it morning (yes/no)? "
read string

if [ $string = "yes" ] ; then
  echo "Good morning"
elif [ $string = "no" ] ; then
  echo "Good afternoon"
else
  echo "Sorry, wrong answer"
fi

exit 0
