#!/bin/bash
set -e

scriptpath=$(realpath $0)
scriptdir=$(dirname $scriptpath)

for d in *; do
    if [ ! -d $d ]; then continue; fi
    if [ $d == out ]; then continue; fi
    for dd in $d/*; do
        echo "==> $dd"
        rm -rf out/$dd/
        mkdir -p out/$dd/
	origdir=$(realpath $dd)
	pushd out/$dd > /dev/null
        g++ -c $origdir/snippet.cpp -O3 -S -fdump-tree-all-graph -masm=intel
        $scriptdir/filter_dot.sh <snippet.cpp.048t.profile_estimate.dot > snippet.cpp.048t.profile_estimate.filtered.dot
	dot ./snippet.cpp.048t.profile_estimate.filtered.dot -Tpng > estimate.png
        $scriptdir/filter_dot.sh <snippet.cpp.244t.optimized.dot > snippet.cpp.244t.optimized.filtered.dot
        dot ./snippet.cpp.244t.optimized.filtered.dot -Tpng > optimized.png
	popd > /dev/null
    done
done

rm out.zip
zip -q out.zip -r out/*

