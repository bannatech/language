#!/bin/bash

cd cases

../tools/test.sh $1

../tools/clean.sh $1 &> /dev/null

cd .. &> /dev/null

rm ../src/*.o &> /dev/null
