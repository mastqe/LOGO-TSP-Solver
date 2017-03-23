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

    # iterate over desired core counts
    for i in 1 2 4 8 16 32 64; do
        printf "cores: $i\n"

        ./logo --in=../tsplib/$file --mode=cpupar --err=0.05f      \
               --showLOInfo=1       --autoDevice  --maxCoresCPU=$i \
               > ./results/${file%.tsp}_${i}_cpu
    done

    # execute on GPU
    printf "GPU\n"
    ./logo --in=../tsplib/$file --mode=cuda --err=0.05f \
           --showLOInfo=1       --autoDevice            \
           > ./results/${file%.tsp}_gpu
done
