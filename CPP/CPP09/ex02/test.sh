#!/bin/bash

for i in {1..5000}
do
    #./PmergeMe `shuf -i 1-100000 -n $i | tr "\n" " "`
    valgrind ./PmergeMe `shuf -i 1-100000 -n $i | tr "\n" " "`
done

#for i in {2..5}
#do
#    for j in {1..5}; do
#        ./PmergeMe `shuf -i 1-100000 -n $i | tr "\n" " "`
#    done
#done
