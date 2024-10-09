#!/bin/bash

# Uso parametri per pulire e archiviare

rm *~
mkdir "$1"
tar -zcvf "$2.tgz" s*.sh
mv "$2.tgz" "./$1"

exit 0
