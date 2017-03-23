#!/bin/bash
#cd LOGO-solver

if [ ! -d "results" ]; then
	mkdir results	
fi

./logo --in=../tsplib/berlin52.tsp --mode=cpu --err=0.005f --showLOInfo=1 --autoDevice |tee results/52_cpu
./logo --in=../tsplib/berlin52.tsp --mode=cpumt --err=0.005f --showLOInfo=1 --autoDevice |tee results/52_cpumt
./logo --in=../tsplib/berlin52.tsp --mode=cuda --err=0.005f --showLOInfo=1 --autoDevice |tee results/52_cuda

./logo --in=../tsplib/kroA100.tsp --mode=cpu --err=0.005f --showLOInfo=1 --autoDevice |tee results/100_cpu
./logo --in=../tsplib/kroA100.tsp --mode=cpumt --err=0.005f --showLOInfo=1 --autoDevice |tee results/100_cpumt
./logo --in=../tsplib/kroA100.tsp --mode=cuda --err=0.005f --showLOInfo=1 --autoDevice |tee results/100_cuda

./logo --in=../tsplib/gr202.tsp --mode=cpu --err=0.005f --showLOInfo=1 --autoDevice |tee results/202_cpu
./logo --in=../tsplib/gr202.tsp --mode=cpumt --err=0.005f --showLOInfo=1 --autoDevice |tee results/202_cpumt
./logo --in=../tsplib/gr202.tsp --mode=cuda --err=0.005f --showLOInfo=1 --autoDevice |tee results/202_cuda

./logo --in=../tsplib/pcb442.tsp --mode=cpu --err=0.01f --showLOInfo=1 --autoDevice |tee results/442_cpu
./logo --in=../tsplib/pcb442.tsp --mode=cpumt --err=0.01f --showLOInfo=1 --autoDevice |tee results/442_cpumt
./logo --in=../tsplib/pcb442.tsp --mode=cuda --err=0.01f --showLOInfo=1 --autoDevice |tee results/442_cuda
