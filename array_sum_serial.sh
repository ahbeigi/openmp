#!/bin/bash

size=$(($1))
sum=$((0))
echo "size = $size"
echo "step = `echo "scale=4;1/$size"|bc`"

for i in `seq 0 $(($size-1))`; do
	tmp=`echo "scale=4;$i/$size"|bc`
	sum=`echo "scale=4;$sum+$tmp"|bc`
done

echo "sum = $sum"
exit 0
