#!/bin/bash
./solve_dynamic.sh $1 $2 0   $3 0 
./solve_dynamic.sh $1 $2 0.5 $3 0 
./solve_dynamic.sh $1 $2 1.0 $3 0 
./solve_dynamic.sh $1 $2 0.5 $3 1 
./solve_dynamic.sh $1 $2 0.5 $3 2 
./solve_dynamic.sh $1 $2 0.5 $3 3 
./solve_dynamic.sh $1 $2 0.5 $3 4 

cat ../../results/$1c_$2a_0p_$3inst_dynamic0.csv   | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_0p_$3inst_dynamic0_tour.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic0.csv | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic0_tour.txt
cat ../../results/$1c_$2a_1.0p_$3inst_dynamic0.csv | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_1.0p_$3inst_dynamic0_tour.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic1.csv | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic1_tour.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic2.csv | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic2_tour.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic3.csv | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic3_tour.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic4.csv | awk -F, '{print $1    }' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic4_tour.txt

paste ../../results/$1c_$2a_0p_$3inst_dynamic0_tour.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic0_tour.txt \
../../results/$1c_$2a_1.0p_$3inst_dynamic0_tour.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic1_tour.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic2_tour.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic3_tour.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic4_tour.txt > ../../results/$1c_$2a_results.xlx

