#!/bin/bash
program=bridges

g++ main.cpp -o $program

for graph in examples/*.txt
do
  echo "-- TEST $graph --"
  ./$program < $graph
done
