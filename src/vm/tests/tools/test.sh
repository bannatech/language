#!/bin/bash

dir=$(ls)

for i in $dir
do
	if [ "$1" == 'all' ] || [ "$1" == $i ]; then
		cd $i
		make
		
		printf "\nTESTCASE: $(basename $PWD)\n"
		printf "The following differences between valid test vs. current test:"
		printf "\n"
		
		./test bytecode | diff /dev/stdin expected_output
		cd ..
	fi
done
