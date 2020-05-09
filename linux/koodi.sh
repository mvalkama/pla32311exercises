#!/bin/bash

echo "Hello world!"
echo $0 $*
echo $(date)
echo "Enter a number"
read val1
echo "Enter a number"
read val2
((sum = $val1 + $val2))
echo "Sum of" $val1 "and" $val2 "is" $sum
