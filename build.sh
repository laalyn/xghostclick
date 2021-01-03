#!/usr/bin/env sh

mkdir cmake-build-release
cd cmake-build-release &&
cmake ../ &&
make &&
cd .. &&
ln -s cmake-build-release/xghostclick launch
