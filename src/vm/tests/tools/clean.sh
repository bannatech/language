#!/bin/bash

dir=$(ls)

for i in $dir
do
	if [ "$1" == 'all' ] || [ "$1" == $i ]; then
		cd $i
		make clean
		cd ..
	fi
done
