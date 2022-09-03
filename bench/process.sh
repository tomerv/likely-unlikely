#!/bin/bash
set -e

for d in *; do
    if [ ! -d $d ]; then continue; fi

    echo "==> $d"
    pushd $d > /dev/null

    g++ --std=c++20 -O2 main.cpp -o main

    echo "Run #1"
    ./main
    echo "Run #2"
    ./main
    echo "Run #3"
    ./main
    echo "Run #4"
    sudo perf stat ./main
    echo "Run #5"
    sudo perf stat -e L1-icache-load-misses,L1-dcache-load-misses,L1-dcache-loads ./main

    popd > /dev/null
done

