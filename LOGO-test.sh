#!/bin/bash

if [ -e "out.txt" ]; then
    rm out.txt
fi

if [ ! -d "results" ]; then
    mkdir results
fi

arg=${1:-1}

for x in $(seq 1 $arg); do
    # iterate over files lists in "tsps"
    for file in $(cat tsps); do
        printf "file: $file\n"

        let num=$(echo $file | sed "s/[a-zA-Z]*//g")

        # execute on GPU
        printf "GPU\n"
        ./logo --in=../tsplib/${file}.tsp --mode=cuda --err=0.05f \
               --showLOInfo=1             --autoDevice            \
               > ./results/${num}_gpu

        # iterate over desired core counts
        for i in 64 32 16 8 4 2 1; do
            printf "cores: $i\n"

            ./logo --in=../tsplib/${file}.tsp --mode=cpupar --err=0.05f      \
                   --showLOInfo=1             --autoDevice  --maxCoresCPU=$i \
                   > ./results/${num}_${i}_cpu
        done
    done

    printf "\n ----- Saving $x -----\n\n"
    ./results.sh
    mv data.csv ${x}.csv
    rm -r results
    mkdir results
done
