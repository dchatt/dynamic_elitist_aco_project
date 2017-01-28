#!/bin/bash

echo "#define MAX_CITIES $1" > ../../src/solver/parameter.h
echo "#define MAX_ANTS $2" >> ../../src/solver/parameter.h
echo "#define PROB_ELITIST $3" >> ../../src/solver/parameter.h

g++ ../../src/solver/antalDynamic.cpp -o ../../bin/solver/solve_dynamic
echo -n "" > ../../results/$1c_$2a_$3p_$4inst_dynamic$5.csv

for (( i=0; i < $4; ++i ))
do
	dirname="../../data/$1c"
	filename="tsp_$1c_instance$i.txt"
	echo solving $dirname/$filename with scheme=$5 static_prob_elitist=$3 $6 
	../../bin/solver/solve_dynamic $dirname/$filename $5 $6 >> ../../results/$1c_$2a_$3p_$4inst_dynamic$5.csv 
done
