#!/bin/bash

if [ $# -lt 2 ] ; then
  echo "Usage: name.sh number format (=o,x,e)" ;
  exit 1 ;
fi

case "$2" in
  o) printf "%o\n" "$1" ;;
  x) printf "%x\n" "$1" ;;
  e) printf "%e\n" "$1" ;;
  *) echo "ERROR: Unknown conversion, $2!" ;;
esac