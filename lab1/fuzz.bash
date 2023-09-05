#!/usr/bin/env bash

rm -rf build_fuzz

CC=/usr/bin/afl-clang-fast
export CC

CXX=/usr/bin/afl-clang-fast++
export CXX

AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1
export AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES

AFL_SKIP_CPUFREQ=1
export AFL_SKIP_CPUFREQ

mkdir build_fuzz
cd build_fuzz
cmake -DFUZZING=OFF ..
cmake --build .

mkdir in out
echo 1 >> in/1
afl-fuzz -i in -o out -- ./lab1

