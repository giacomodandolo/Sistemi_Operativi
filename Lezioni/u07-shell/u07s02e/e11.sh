#!/bin/bash

echo -n "Is it morning (yes/no)? "
read string

if [ $string = "yes" ] ; then
  echo "Good morning"
else
  echo "Good afternoon"
fi

exit 0
