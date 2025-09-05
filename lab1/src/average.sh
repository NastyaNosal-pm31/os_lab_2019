#!/bin/bash
x=0
counter=0
while read arg 
do
    x=$[$arg+$x]
    counter=$[$counter+1]
done
echo 'кол-во входных параметров':$counter
awk "BEGIN{print $x/$counter}"
 