#!/bin/bash

dir=$(ls)

successes=0
total=0
for i in $dir
do
	if [ "$1" == 'all' ] || [ "$1" == $i ]; then
		total=$((total + 1))

		cd $i
		make &> /dev/null

		printf "\nTESTCASE: $(basename $PWD)\n"
		
		if (./test | diff /dev/stdin expected_output &> /dev/null); then
			printf "TESTCASE $(basename $PWD) succeeded\n"
			successes=$((successes + 1))
		else
			printf "TESTCASE $(basename $PWD) failed\n"
			printf "$output\n"
		fi

		cd ..
	fi
done

printf "PASSING: $successes/$total\n"
