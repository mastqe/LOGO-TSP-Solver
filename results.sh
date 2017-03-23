#!/bin/bash

# get final found length of path
function length {
	printf "%s %s\n" "final length: " $(cat results/442_cuda | grep "New global minimum" | tail -n1 | cut -d">" -f2 | cut -d" " -f3)
	
}

# get time
function path_time {
	printf "%s %s\n" "path time: " $(tail -n1 $1 | cut -d" " -f 3)
}

# get accuracy
function acc {
	printf "%s %s\n" "final accuracy: " $(cat results/442_cuda | grep "New global minimum" | tail -n1 | cut -d">" -f2 | cut -d" " -f5)
}

for f in results/*; do
	printf "%s\n" "File: $f {"
	
		printf "\t"; length 	$f
		printf "\t"; acc 		$f
		printf "\t"; path_time 	$f

	printf "}\n\n" 
done

