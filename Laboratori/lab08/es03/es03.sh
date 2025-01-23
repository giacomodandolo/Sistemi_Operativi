#!/bin/bash

if test $# -ne 1
then
    echo "Usage: $0 directory"
fi

ls $1 | while read line
do
    mv $1/$line $1/`echo $line | tr a-z A-Z`
done
