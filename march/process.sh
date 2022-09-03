#!/bin/bash
set -e

rm -rf out

echo "=== Compiling... ==="
for d in *; do
    if [ ! -d $d ]; then continue; fi
    echo "==> $d"
    mkdir -p out/$d
    origdir=$(realpath $d)
    pushd out/$d > /dev/null
    g++ $origdir/main.cpp --std=c++20 -O2 -o main_O2
    g++ $origdir/main.cpp --std=c++20 -O3 -o main_O3
    g++ $origdir/main.cpp --std=c++20 -O2 -march=native -o main_O2_native
    g++ $origdir/main.cpp --std=c++20 -O3 -march=native -o main_O3_native
    popd > /dev/null
done
echo

for flavor in O2 O3 O2_native O3_native; do
    echo "=== $flavor ==="
    for d in out/*; do
        t=$d/main_$flavor
        $t > /dev/null
        $t > /dev/null
        $t
    done
done

