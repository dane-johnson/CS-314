#!/bin/bash
if [ ! -f numbers ]; then echo 0 > numbers; fi 
count=0
while [[ $count != 100 ]]; do
    while true; do
	if ln numbers numbers.lock 2> /dev/null; then break; fi;
    done
    next=`tail -n 1 numbers`
    next=`expr $next + 1`
    echo $next >> numbers
    count=`expr $count + 1`
    rm numbers.lock
done
