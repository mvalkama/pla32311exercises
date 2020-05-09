#!/bin/bash

function readPositiveInt() {
  local val
  until [[ $val =~ ^[0-9]+$ ]]
        do    
          echo "Enter a number"
          read val
  done
  
  return $val;
}

echo "Hello world!"
echo $0 $*
echo $(date)
readPositiveInt
((val1 = $?))
readPositiveInt
((val2 = $?))

((sum = $val1 + $val2))
echo "Sum of" $val1 "and" $val2 "is" $sum

