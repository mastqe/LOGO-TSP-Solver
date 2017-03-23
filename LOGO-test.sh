#!/bin/bash

if [ -e "out.txt" ]; then
    rm out.txt
fi

if [ ! -d "results" ]; then
    mkdir results   
fi

# iterate over files lists in "tsps"
for file in $(cat tsps); do
    printf "file: $file\n"

    let num=$(echo $file | sed "s/[a-z]*//g")

    # iterate over desired core counts
    for i in 1 2 4 8 16 32 64; do
        printf "cores: $i\n"

        ./logo --in=../tsplib/${file}.tsp --mode=cpupar --err=0.05f      \
               --showLOInfo=1             --autoDevice  --maxCoresCPU=$i \
               > ./results/${num}_${i}_cpu
    done

    # execute on GPU
    printf "GPU\n"
    ./logo --in=../tsplib/${file}.tsp --mode=cuda --err=0.05f \
           --showLOInfo=1             --autoDevice            \
           > ./results/${num}_gpu
done
