#!/bin/bash

# In this new script we need to manually make sure these arrays stay aligned
algs=( enum bnb dp greedy )
inputs=( 'easy.20.1.txt' 'easy.200.4.txt' 'hard1.200.11.txt' 'hard1.2000.1.txt' )
times=( 5 5 60 60 )
solutions=( 377 4077 126968 - )

function get_index () {
  value=$1
  INDEX=-1
  index=0
  for x in ${inputs[@]}; do
    if [ "$x" == "${value}" ]; then
      INDEX=$index
    fi
    index=$((index+1))
  done
}
function timeout() { perl -e 'alarm shift; exec @ARGV' "$@"; }


for FILE in ${inputs[@]}
do
  #This line sets gobal variable INDEX
  get_index $FILE
  LIMIT="${times[$INDEX]}"
  echo "==========================================="
  echo "Running on $FILE for $LIMIT seconds"
  echo "==========================================="
  echo
  echo "Algorithm |      Optimal Value       | Time Taken  | Result"
  echo "----------------------------------------------------------------"
  for alg in ${algs[@]}
  do
    TIME=$({ time timeout ${LIMIT}s ./$alg $FILE > ${alg}_${FILE}_out ; } 2>&1 | grep real | grep -o '[0-9].*')
    LAST=$(grep -o '\(Current best solution\|value\)=[0-9]*' ${alg}_${FILE}_out | tail -1)
    VALUE=$(echo $LAST | sed -E  's/.*=([0-9]+).*/\1/')
    CORRECT="?"
    if [ -z $VALUE ]  && [ $alg != "greedy" ]
    then
      VALUE="-"
      CORRECT="-"
    fi
    if [ $alg != "greedy" ]
    then
      ANSWER="${solutions[$INDEX]}"
      if [ $ANSWER == $VALUE ]
      then
        CORRECT="Yes"
      else
        CORRECT="No"
      fi
      if [[ "$LAST" == *Current* ]]
      then
        CORRECT="?"
        VALUE="$VALUE (after ${LIMIT}s)"
      fi
    fi
    printf -v alg %-10.10s $alg
    printf -v VALUE %-25.25s "$VALUE"
    echo "$alg| $VALUE| ${TIME}    | $CORRECT"
  done
  echo
  echo
done
