#!/bin/bash
./solve_dynamic.sh $1 $2 0   $3 0 
./solve_dynamic.sh $1 $2 0.5 $3 0 
./solve_dynamic.sh $1 $2 1.0 $3 0 
./solve_dynamic.sh $1 $2 0.5 $3 1 
./solve_dynamic.sh $1 $2 0.5 $3 2 
./solve_dynamic.sh $1 $2 0.5 $3 3 
./solve_dynamic.sh $1 $2 0.5 $3 4 

./combine_results.sh $1 $2 $3

