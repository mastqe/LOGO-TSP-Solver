/*
 *   Logo TSP Solver ver. 0.62  Copyright (C) 2013  Kamil Rocki
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cutil.h>
#include <headers.h>

cmdArguments
parseInput(int argc, const char **argv)
{
    cmdArguments    args;
    char           *inputArg = NULL;
    trace("----------\n");
    trace("Setting parameters...\n");
    // for the default values see defs.h
    args.filename = (char *) DEFAULT_FILENAME;
    args.outfilename = (char *) DEFAULT_OUT;
    args.gpuThreads = DEFAULT_GPU_THREADS;
    args.gpuBlocks = DEFAULT_GPU_BLOCKS;
    args.pthreads = DEFAULT_PTHREADS;
    args.setAffinity = DEFAULT_AFFINITY;
    args.timelimit = DEFAULT_TIMELIMIT;
    args.error = DEFAULT_ERROR_TOLERANCE;
    args.initRouteFromFile = 0;
    args.initMethod = (char *) DEFAULT_INIT;
    args.mode = DEFAULT_MODE;
    args.device = -1;
    args.autoDevice = 0;
    args.maxKicks = 0;
    args.stallIterations = DEFAULT_STALL_ITERS;
    args.backtracking = (char *) DEFAULT_BACKTRACKING;
    args.backtrackingLimit = DEFAULT_BACKTRACKING_LIMIT;
    args.stallIterations = DEFAULT_STALL_ITERS;
    args.stallTimePeriod = DEFAULT_STALL_TIME_PERIOD;
    args.stallTimeMultiplier = DEFAULT_STALL_TIME_MULTIPLIER;
    args.showLocalOptimizationInfo = DEFAULT_SHOW_LO_INFO;
    args.comm = DEFAULT_PTHREADS_COMM;
    args.commPart = DEFAULT_PTHREADS_COMM_PART;
    args.trackSolution = DEFAULT_TRACK_SOLUTION;
    args.benchmark = 0;
    args.maxDevices = -1;
#ifdef DEFAULT_MAX_CORES
    args.maxCoresUsed = DEFAULT_MAX_CORES;
#else
    args.maxCoresUsed = 32;
#endif

    // number of cpu threads to be used (if using parallel cpu computation)
    if (cutGetCmdLineArgumentstr(argc, argv, "pthreads", &inputArg)) {
	args.pthreads = atoi(inputArg);
    }

    if (cutGetCmdLineArgumentstr(argc, argv, "setAffinity", &inputArg)) {
	args.setAffinity = atoi(inputArg);
    }

    if (cutGetCmdLineArgumentstr(argc, argv, "maxCoresCPU", &inputArg)) {
	args.maxCoresUsed = atoi(inputArg);
    }

    if (cutGetCmdLineArgumentstr(argc, argv, "cpuvector", &inputArg)) {
	args.vectorsize = atoi(inputArg);
    }
    // file for writing output data
    if (cutGetCmdLineArgumentstr(argc, argv, "out", &inputArg)) {
	args.outfilename = inputArg;
    }
    // input (TSPLIB format) file
    if (cutGetCmdLineArgumentstr(argc, argv, "in", &inputArg)) {
	args.filename = (char *) inputArg;
    }
    // CUDA blocks
    if (cutGetCmdLineArgumentstr(argc, argv, "blocks", &inputArg)) {
	args.gpuBlocks = atoi(inputArg);
    }
    // CUDA threads per block
    if (cutGetCmdLineArgumentstr(argc, argv, "threads", &inputArg)) {
	args.gpuThreads = atoi(inputArg);
    }
    // Time limit (if used)
    if (cutGetCmdLineArgumentstr(argc, argv, "timelimit", &inputArg)) {
	args.timelimit = atof(inputArg);
    }
    // Acceptable distance to the optimal (or best known) solution
    if (cutGetCmdLineArgumentstr(argc, argv, "err", &inputArg)) {
	args.error = atof(inputArg);
    }
    // init from a saved tour
    if (cutGetCmdLineArgumentstr(argc, argv, "initRouteFromFile", &inputArg)) {
	args.initRouteFromFile = atoi(inputArg);
    }
    // tour to be loaded
    if (cutGetCmdLineArgumentstr(argc, argv, "initRouteFile", &inputArg)) {
	args.initRouteFile = (char *) inputArg;
    }
    // tour construction method
    if (cutGetCmdLineArgumentstr(argc, argv, "initMethod", &inputArg)) {
	args.initMethod = (char *) inputArg;
    }
    // mode
    if (cutGetCmdLineArgumentstr(argc, argv, "mode", &inputArg)) {
	if (!strcmp((char *) inputArg, "cpu")) {
	    args.mode = MODE_CPU;

	} else if (!strcmp((char *) inputArg, "cuda")) {
	    args.mode = MODE_CUDA;

	} else if (!strcmp((char *) inputArg, "cl")) {
	    args.mode = MODE_OPENCL;

	} else if (!strcmp((char *) inputArg, "all")) {
	    args.mode = MODE_ALL;

	} else if (!strcmp((char *) inputArg, "cpumt")) {
	    args.mode = MODE_CPU_ALL;

	} else if (!strcmp((char *) inputArg, "cpupar")) {
	    args.mode = MODE_CPU_PARALLEL;

	} else if (!strcmp((char *) inputArg, "cpuhybrid")) {
	    args.mode = MODE_CPU_PARALLEL_HYBRID;
	}
    }

    if (cutGetCmdLineArgumentstr(argc, argv, "benchmark", &inputArg)) {
	args.benchmark = atoi(inputArg);
    }

    if (cutGetCmdLineArgumentstr(argc, argv, "device", &inputArg)) {
	args.device = atoi(inputArg);
    }

    if (cutGetCmdLineArgumentstr(argc, argv, "autoDevice", &inputArg)) {
	args.autoDevice = 1;
    }

    if (cutGetCmdLineArgumentstr(argc, argv, "maxDevices", &inputArg)) {
	args.maxDevices = atoi(inputArg);
    }
    // perturbation, no of kicks
    if (cutGetCmdLineArgumentstr(argc, argv, "maxKicks", &inputArg)) {
	args.maxKicks = atoi(inputArg);
    }
    // backtracking, type
    if (cutGetCmdLineArgumentstr(argc, argv, "backtracking", &inputArg)) {
	args.backtracking = (char *) (inputArg);
    }
    // backtracking, every n iterations
    if (cutGetCmdLineArgumentstr(argc, argv, "stallIterations", &inputArg)) {
	args.stallIterations = atoi(inputArg);
    }
    // backtracking, max moves back divider
    if (cutGetCmdLineArgumentstr(argc, argv, "backtrackingLimit", &inputArg)) {
	args.backtrackingLimit = atoi(inputArg);
    }
    // backtracking, time (last values considered)
    if (cutGetCmdLineArgumentstr(argc, argv, "stallTimePeriod", &inputArg)) {
	args.stallTimePeriod = atoi(inputArg);
    }
    // backtracking, time (multiplier)
    if (cutGetCmdLineArgumentstr(argc, argv, "stallTimeMultiplier", &inputArg)) {
	args.stallTimeMultiplier = atoi(inputArg);
    }
    // local optimization messages
    if (cutGetCmdLineArgumentstr(argc, argv, "showLOInfo", &inputArg)) {
	args.showLocalOptimizationInfo = atoi(inputArg);
    }
    // inter-thread communication
    if (cutGetCmdLineArgumentstr(argc, argv, "comm", &inputArg)) {
	args.comm = atoi(inputArg);
    }
    // define part of the threads to communicate
    if (cutGetCmdLineArgumentstr(argc, argv, "commPart", &inputArg)) {
	args.commPart = atof(inputArg);
    }

    if (cutGetCmdLineArgumentstr(argc, argv, "trackSolution", &inputArg)) {
	args.trackSolution = atoi(inputArg);
    }

    if (args.commPart < 0.0f) {
	args.commPart = 0.0f;
    }

    if (args.commPart > 1.0f) {
	args.commPart = 1.0f;
    }

    if (args.error < 0.0f) {
	args.error = 0.0f;
    }
    // some known solutions to compare with during the computation
    if (!strcmp(args.filename, "../tsplib/a280.tsp")) {
        args.solution = 2579;

    } else if (!strcmp(args.filename, "../tsplib/ali535.tsp")) {
        args.solution = 202339;

    } else if (!strcmp(args.filename, "../tsplib/att48.tsp")) {
        args.solution = 10628;

    } else if (!strcmp(args.filename, "../tsplib/att532.tsp")) {
        args.solution = 27686;

    } else if (!strcmp(args.filename, "../tsplib/bayg29.tsp")) {
        args.solution = 1610;

    } else if (!strcmp(args.filename, "../tsplib/bays29.tsp")) {
        args.solution = 2020;

    } else if (!strcmp(args.filename, "../tsplib/berlin52.tsp")) {
        args.solution = 7542;

    } else if (!strcmp(args.filename, "../tsplib/bier127.tsp")) {
        args.solution = 118282;

    } else if (!strcmp(args.filename, "../tsplib/brazil58.tsp")) {
        args.solution = 25395;

    } else if (!strcmp(args.filename, "../tsplib/brd14051.tsp")) {
        args.solution = 469385;

    } else if (!strcmp(args.filename, "../tsplib/brg180.tsp")) {
        args.solution = 1950;

    } else if (!strcmp(args.filename, "../tsplib/burma14.tsp")) {
        args.solution = 3323;

    } else if (!strcmp(args.filename, "../tsplib/ch130.tsp")) {
        args.solution = 6110;

    } else if (!strcmp(args.filename, "../tsplib/ch150.tsp")) {
        args.solution = 6528;

    } else if (!strcmp(args.filename, "../tsplib/d1291.tsp")) {
        args.solution = 50801;

    } else if (!strcmp(args.filename, "../tsplib/d15112.tsp")) {
        args.solution = 1573084;

    } else if (!strcmp(args.filename, "../tsplib/d1655.tsp")) {
        args.solution = 62128;

    } else if (!strcmp(args.filename, "../tsplib/d18512.tsp")) {
        args.solution = 645238;

    } else if (!strcmp(args.filename, "../tsplib/d198.tsp")) {
        args.solution = 15780;

    } else if (!strcmp(args.filename, "../tsplib/d2103.tsp")) {
        args.solution = 80450;

    } else if (!strcmp(args.filename, "../tsplib/d493.tsp")) {
        args.solution = 35002;

    } else if (!strcmp(args.filename, "../tsplib/d657.tsp")) {
        args.solution = 48912;

    } else if (!strcmp(args.filename, "../tsplib/dantzig42.tsp")) {
        args.solution = 699;

    } else if (!strcmp(args.filename, "../tsplib/dsj1000.tsp")) {
        args.solution = 18659688;

    } else if (!strcmp(args.filename, "../tsplib/eil101.tsp")) {
        args.solution = 629;

    } else if (!strcmp(args.filename, "../tsplib/eil51.tsp")) {
        args.solution = 426;

    } else if (!strcmp(args.filename, "../tsplib/eil76.tsp")) {
        args.solution = 538;

    } else if (!strcmp(args.filename, "../tsplib/fl1400.tsp")) {
        args.solution = 20127;

    } else if (!strcmp(args.filename, "../tsplib/fl1577.tsp")) {
        args.solution = 22249;

    } else if (!strcmp(args.filename, "../tsplib/fl3795.tsp")) {
        args.solution = 28772;

    } else if (!strcmp(args.filename, "../tsplib/fl417.tsp")) {
        args.solution = 11861;

    } else if (!strcmp(args.filename, "../tsplib/fnl4461.tsp")) {
        args.solution = 182566;

    } else if (!strcmp(args.filename, "../tsplib/fri26.tsp")) {
        args.solution = 937;

    } else if (!strcmp(args.filename, "../tsplib/gil262.tsp")) {
        args.solution = 2378;

    } else if (!strcmp(args.filename, "../tsplib/gr120.tsp")) {
        args.solution = 6942;

    } else if (!strcmp(args.filename, "../tsplib/gr137.tsp")) {
        args.solution = 69853;

    } else if (!strcmp(args.filename, "../tsplib/gr17.tsp")) {
        args.solution = 2085;

    } else if (!strcmp(args.filename, "../tsplib/gr202.tsp")) {
        args.solution = 40160;

    } else if (!strcmp(args.filename, "../tsplib/gr21.tsp")) {
        args.solution = 2707;

    } else if (!strcmp(args.filename, "../tsplib/gr229.tsp")) {
        args.solution = 134602;

    } else if (!strcmp(args.filename, "../tsplib/gr24.tsp")) {
        args.solution = 1272;

    } else if (!strcmp(args.filename, "../tsplib/gr431.tsp")) {
        args.solution = 171414;

    } else if (!strcmp(args.filename, "../tsplib/gr48.tsp")) {
        args.solution = 5046;

    } else if (!strcmp(args.filename, "../tsplib/gr666.tsp")) {
        args.solution = 294358;

    } else if (!strcmp(args.filename, "../tsplib/gr96.tsp")) {
        args.solution = 55209;

    } else if (!strcmp(args.filename, "../tsplib/hk48.tsp")) {
        args.solution = 11461;

    } else if (!strcmp(args.filename, "../tsplib/kroA100.tsp")) {
        args.solution = 21282;

    } else if (!strcmp(args.filename, "../tsplib/kroA150.tsp")) {
        args.solution = 26524;

    } else if (!strcmp(args.filename, "../tsplib/kroA200.tsp")) {
        args.solution = 29368;

    } else if (!strcmp(args.filename, "../tsplib/kroB100.tsp")) {
        args.solution = 22141;

    } else if (!strcmp(args.filename, "../tsplib/kroB150.tsp")) {
        args.solution = 26130;

    } else if (!strcmp(args.filename, "../tsplib/kroB200.tsp")) {
        args.solution = 29437;

    } else if (!strcmp(args.filename, "../tsplib/kroC100.tsp")) {
        args.solution = 20749;

    } else if (!strcmp(args.filename, "../tsplib/kroD100.tsp")) {
        args.solution = 21294;

    } else if (!strcmp(args.filename, "../tsplib/kroE100.tsp")) {
        args.solution = 22068;

    } else if (!strcmp(args.filename, "../tsplib/lin105.tsp")) {
        args.solution = 14379;

    } else if (!strcmp(args.filename, "../tsplib/lin318.tsp")) {
        args.solution = 42029;

    } else if (!strcmp(args.filename, "../tsplib/linhp318.tsp")) {
        args.solution = 41345;

    } else if (!strcmp(args.filename, "../tsplib/nrw1379.tsp")) {
        args.solution = 56638;

    } else if (!strcmp(args.filename, "../tsplib/p654.tsp")) {
        args.solution = 34643;

    } else if (!strcmp(args.filename, "../tsplib/pa561.tsp")) {
        args.solution = 2763;

    } else if (!strcmp(args.filename, "../tsplib/pcb1173.tsp")) {
        args.solution = 56892;

    } else if (!strcmp(args.filename, "../tsplib/pcb3038.tsp")) {
        args.solution = 137694;

    } else if (!strcmp(args.filename, "../tsplib/pcb442.tsp")) {
        args.solution = 50778;

    } else if (!strcmp(args.filename, "../tsplib/pla33810.tsp")) {
        args.solution = 66048945;

    } else if (!strcmp(args.filename, "../tsplib/pla7397.tsp")) {
        args.solution = 23260728;

    } else if (!strcmp(args.filename, "../tsplib/pla85900.tsp")) {
        args.solution = 142382641;

    } else if (!strcmp(args.filename, "../tsplib/pr1002.tsp")) {
        args.solution = 259045;

    } else if (!strcmp(args.filename, "../tsplib/pr107.tsp")) {
        args.solution = 44303;

    } else if (!strcmp(args.filename, "../tsplib/pr124.tsp")) {
        args.solution = 59030;

    } else if (!strcmp(args.filename, "../tsplib/pr136.tsp")) {
        args.solution = 96772;

    } else if (!strcmp(args.filename, "../tsplib/pr144.tsp")) {
        args.solution = 58537;

    } else if (!strcmp(args.filename, "../tsplib/pr152.tsp")) {
        args.solution = 73682;

    } else if (!strcmp(args.filename, "../tsplib/pr226.tsp")) {
        args.solution = 80369;

    } else if (!strcmp(args.filename, "../tsplib/pr2392.tsp")) {
        args.solution = 378032;

    } else if (!strcmp(args.filename, "../tsplib/pr264.tsp")) {
        args.solution = 49135;

    } else if (!strcmp(args.filename, "../tsplib/pr299.tsp")) {
        args.solution = 48191;

    } else if (!strcmp(args.filename, "../tsplib/pr439.tsp")) {
        args.solution = 107217;

    } else if (!strcmp(args.filename, "../tsplib/pr76.tsp")) {
        args.solution = 108159;

    } else if (!strcmp(args.filename, "../tsplib/rat195.tsp")) {
        args.solution = 2323;

    } else if (!strcmp(args.filename, "../tsplib/rat575.tsp")) {
        args.solution = 6773;

    } else if (!strcmp(args.filename, "../tsplib/rat783.tsp")) {
        args.solution = 8806;

    } else if (!strcmp(args.filename, "../tsplib/rat99.tsp")) {
        args.solution = 1211;

    } else if (!strcmp(args.filename, "../tsplib/rd100.tsp")) {
        args.solution = 7910;

    } else if (!strcmp(args.filename, "../tsplib/rd400.tsp")) {
        args.solution = 15281;

    } else if (!strcmp(args.filename, "../tsplib/rl11849.tsp")) {
        args.solution = 923288;

    } else if (!strcmp(args.filename, "../tsplib/rl1304.tsp")) {
        args.solution = 252948;

    } else if (!strcmp(args.filename, "../tsplib/rl1323.tsp")) {
        args.solution = 270199;

    } else if (!strcmp(args.filename, "../tsplib/rl1889.tsp")) {
        args.solution = 316536;

    } else if (!strcmp(args.filename, "../tsplib/rl5915.tsp")) {
        args.solution = 565530;

    } else if (!strcmp(args.filename, "../tsplib/rl5934.tsp")) {
        args.solution = 556045;

    } else if (!strcmp(args.filename, "../tsplib/si1032.tsp")) {
        args.solution = 92650;

    } else if (!strcmp(args.filename, "../tsplib/si175.tsp")) {
        args.solution = 21407;

    } else if (!strcmp(args.filename, "../tsplib/si535.tsp")) {
        args.solution = 48450;

    } else if (!strcmp(args.filename, "../tsplib/st70.tsp")) {
        args.solution = 675;

    } else if (!strcmp(args.filename, "../tsplib/swiss42.tsp")) {
        args.solution = 1273;

    } else if (!strcmp(args.filename, "../tsplib/ts225.tsp")) {
        args.solution = 126643;

    } else if (!strcmp(args.filename, "../tsplib/tsp225.tsp")) {
        args.solution = 3916;

    } else if (!strcmp(args.filename, "../tsplib/u1060.tsp")) {
        args.solution = 224094;

    } else if (!strcmp(args.filename, "../tsplib/u1432.tsp")) {
        args.solution = 152970;

    } else if (!strcmp(args.filename, "../tsplib/u159.tsp")) {
        args.solution = 42080;

    } else if (!strcmp(args.filename, "../tsplib/u1817.tsp")) {
        args.solution = 57201;

    } else if (!strcmp(args.filename, "../tsplib/u2152.tsp")) {
        args.solution = 64253;

    } else if (!strcmp(args.filename, "../tsplib/u2319.tsp")) {
        args.solution = 234256;

    } else if (!strcmp(args.filename, "../tsplib/u574.tsp")) {
        args.solution = 36905;

    } else if (!strcmp(args.filename, "../tsplib/u724.tsp")) {
        args.solution = 41910;

    } else if (!strcmp(args.filename, "../tsplib/ulysses16.tsp")) {
        args.solution = 6859;

    } else if (!strcmp(args.filename, "../tsplib/ulysses22.tsp")) {
        args.solution = 7013;

    } else if (!strcmp(args.filename, "../tsplib/usa13509.tsp")) {
        args.solution = 19982859;

    } else if (!strcmp(args.filename, "../tsplib/vm1084.tsp")) {
        args.solution = 239297;

    } else if (!strcmp(args.filename, "../tsplib/vm1748.tsp")) {
        args.solution = 336556;
    
    } else {
	args.solution = INT_MAX;
    }

    // Summary
    trace("Done.\n");
    trace("----------\n");
    trace("Input filename = %s\n", args.filename);
    trace("Output filename = %s\n", args.outfilename);
    trace("Length of the best known solution = %ld\n", args.solution);
    trace("Pthreads = %d\n", args.pthreads);
    trace("Max number of CPU cores to be used = %d\n", args.maxCoresUsed);
    trace("Sched_setaffinity = %d\n", args.setAffinity);
    trace("Inter-thread communication = %d\n", args.comm);
    trace("Backtracking: %s, StallIterations: %d, BacktrackingLimit: %d,\n",
	  args.backtracking, args.stallIterations, args.backtrackingLimit);
    trace("StallTimePeriod: %d, StallTimeMultiplier: %d\n", args.stallTimePeriod,
	  args.stallTimeMultiplier);
    // trace("GPU Threads = %d\n", args.gpuThreads);
    // trace("GPU Blocks = %d\n", args.gpuBlocks);
    trace("Time limit = %.3f s\n", args.timelimit);
    trace("Error tolerance = %.3f%% \n", args.error * 100.0f);
    trace("Init method = %s\n", args.initMethod);
    trace("----------\n");
    return args;
}
