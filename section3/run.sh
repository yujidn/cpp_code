#!/bin/sh

cmake CMakeLists.txt
make

./chrono_cost
echo
./chrono_sample
echo
./chrono_stdev
echo
./gprof_sample
echo
./inf_loop
