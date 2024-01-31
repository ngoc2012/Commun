#!/bin/bash

for i in {1..5}
do
    valgrind ./exe `shuf -i 1-100000 -n $i | tr "\n" " "`
done

