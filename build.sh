#!/usr/bin/env sh

mkdir cmake-build-release
cd cmake-build-release &&
cmake ../ &&
make -j 4 &&
cd .. &&
mkdir configs
ln -s cmake-build-release/xghostclick launch
