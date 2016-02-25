#!/bin/bash

cd cases

../tools/test.sh $1

../tools/clean.sh $1
