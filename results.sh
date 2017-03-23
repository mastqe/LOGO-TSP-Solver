#!/bin/bash

# get final found length of path
function length
{
    printf "%s" $(cat $1 | grep "New global minimum" | tail -n1 | cut -d">" -f2 | cut -d" " -f3)
}

# get time
function path_time
{
    printf "%s" $(tail -n1 $1 | cut -d" " -f 3)
}

# get accuracy
function acc
{
    printf "%s" $(cat $1 | grep "New global minimum" | tail -n1 | cut -d">" -f2 | cut -d" " -f5)
}

for f in results/*; do
    printf "%s,"  ${f:8}
    printf "%s,"  $(length $f)
    printf "%s,"  $(acc $f)
    printf "%s\n" $(path_time $f)
done

