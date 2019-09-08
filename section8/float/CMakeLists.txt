cmake_minimum_required(VERSION 3.0.0)
project(CPPBookCode VERSION 1.0.0)

# 基本オプション 
SET( CMAKE_CXX_COMPILER g++ )
# set(CMAKE_CXX_FLAGS "-std=c++14 -O3 -march=native")
set(CMAKE_CXX_FLAGS "-std=c++17 -ltbb -O3")
# 追加オプション
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# コンパイルオプション基本セット
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wendif-labels -Wfloat-equal -Winit-self -Winline -Wlogical-op -Wmissing-include-dirs -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-promo -Wswitch-default -Wswitch-enum -Wunsafe-loop-optimizations -Wvariadic-macros -Wwrite-strings ")
# set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
# set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native")
# set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
# set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -s -DNDEBUG -march=native")

add_executable(parallel_all_of parallel_all_of.cpp)
add_executable(parallel_count parallel_count.cpp)
add_executable(parallel_copy parallel_copy.cpp)
add_executable(parallel_find parallel_find.cpp)
add_executable(parallel_for_each parallel_for_each.cpp)
add_executable(parallel_remove parallel_remove.cpp)
add_executable(parallel_sort parallel_sort.cpp)
add_executable(parallel_sort_sorted parallel_sort_sorted.cpp)
add_executable(parallel_stable_sort parallel_stable_sort.cpp)
add_executable(parallel_stable_sort_sorted parallel_stable_sort_sorted.cpp)
add_executable(parallel_upper_bound parallel_upper_bound.cpp)
add_executable(parallel_lower_bound parallel_lower_bound.cpp)

