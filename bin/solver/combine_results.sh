#!/bin/bash
cat ../../results/$1c_$2a_0p_$3inst_dynamic0.csv   | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_0p_$3inst_dynamic0_tour.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic0.csv | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic0_tour.txt
cat ../../results/$1c_$2a_1.0p_$3inst_dynamic0.csv | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_1.0p_$3inst_dynamic0_tour.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic1.csv | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic1_tour.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic2.csv | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic2_tour.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic3.csv | awk -F, '{print $1 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic3_tour.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic4.csv | awk -F, '{print $1    }' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic4_tour.txt

cat ../../results/$1c_$2a_0p_$3inst_dynamic0.csv   | awk -F, '{print $2 ","}' >  ../../results/$1c_$2a_0p_$3inst_dynamic0_iter.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic0.csv | awk -F, '{print $2 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic0_iter.txt
cat ../../results/$1c_$2a_1.0p_$3inst_dynamic0.csv | awk -F, '{print $2 ","}' >  ../../results/$1c_$2a_1.0p_$3inst_dynamic0_iter.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic1.csv | awk -F, '{print $2 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic1_iter.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic2.csv | awk -F, '{print $2 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic2_iter.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic3.csv | awk -F, '{print $2 ","}' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic3_iter.txt
cat ../../results/$1c_$2a_0.5p_$3inst_dynamic4.csv | awk -F, '{print $2    }' >  ../../results/$1c_$2a_0.5p_$3inst_dynamic4_iter.txt

paste ../../results/$1c_$2a_0p_$3inst_dynamic0_tour.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic0_tour.txt \
../../results/$1c_$2a_1.0p_$3inst_dynamic0_tour.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic1_tour.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic2_tour.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic3_tour.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic4_tour.txt > ../../results/$1c_$2a_results_tour.xlx

paste ../../results/$1c_$2a_0p_$3inst_dynamic0_iter.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic0_iter.txt \
../../results/$1c_$2a_1.0p_$3inst_dynamic0_iter.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic1_iter.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic2_iter.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic3_iter.txt \
../../results/$1c_$2a_0.5p_$3inst_dynamic4_iter.txt > ../../results/$1c_$2a_results_iter.xlx