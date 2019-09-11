cmake_minimum_required(VERSION 3.0.0)
project(CPPBookCode VERSION 1.0.0)

# 基本オプション 
SET( CMAKE_CXX_COMPILER g++ )
set(CMAKE_CXX_FLAGS "-std=c++14 -O2")
# 追加オプション
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -mavx")

# コンパイルオプション基本セット
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wendif-labels -Wfloat-equal -Winit-self -Winline -Wlogical-op -Wmissing-include-dirs -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-promo -Wswitch-default -Wswitch-enum -Wunsafe-loop-optimizations -Wvariadic-macros -Wwrite-strings ")
# set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
# set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native")
# set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
# set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -s -DNDEBUG -march=native")

# 
add_executable(memory memory.cpp)
add_executable(pipline pipline.cpp)

