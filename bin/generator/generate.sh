#!/bin/bash

echo "#define MAX_CITIES $1" > ../../src/generator/TSPConstructor.h
echo "#define MAX_DIST 100" >> ../../src/generator/TSPConstructor.h

g++ ../../src/generator/TSPConstructor.cpp -o ../../bin/generator/construct

dirname="../../data/$1c"
mkdir $dirname

for (( i=0; i < $2; ++i ))
do	
	filename="tsp_$1c_instance$i.txt"
	echo generating $dirname/$filename
	../../bin/generator/construct $dirname/$filename
	sleep 1
done
