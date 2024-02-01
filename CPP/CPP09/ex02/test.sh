#!/bin/bash

for i in {5..100}
do
    ./exe `shuf -i 1-100000 -n $i | tr "\n" " "`
    #valgrind ./exe `shuf -i 1-100000 -n $i | tr "\n" " "`
done

