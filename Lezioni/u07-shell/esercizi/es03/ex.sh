#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Uso scorretto."
	exit
fi

for path in $*
do
	if [ -f $path ]
	then
		dim=$(ls -l $path | tr -s " " | cut -d " " -f 5)
		read_perm=""
		if [ -r $path ]
		then
			read_perm="R"
		fi
		write_perm=""
		if [ -w $path ]
		then
			write_perm="W"
		fi
		echo "FILE: $path $dim $read_perm $write_perm"
	elif [ -d $path ]
	then
		subdirs=$(find $path -maxdepth 1 -mindepth 1 -type d | wc -l)
		echo "DIR: $path $subdirs"

	fi
done
