#!/bin/bash

#for i in {5..5000}
#do
#    ./exe `shuf -i 1-100000 -n $i | tr "\n" " "`
#    #valgrind ./exe `shuf -i 1-100000 -n $i | tr "\n" " "`
#done

for i in {1..5}
do
    ./exe `shuf -i 1-100000 -n $i | tr "\n" " "`
    #valgrind ./exe `shuf -i 1-100000 -n $i | tr "\n" " "`
done
