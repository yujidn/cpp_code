#!/bin/sh

cmake CMakeLists.txt
make

./parallel_all_of
echo
./parallel_copy
echo
./parallel_count
echo
./parallel_find
echo
./parallel_for_each
echo
./parallel_lower_bound
echo
./parallel_remove
echo
./parallel_sort
echo
./parallel_sort_sorted
echo
./parallel_stable_sort
echo
./parallel_stable_sort_sorted
echo
./parallel_upper_bound
echo
