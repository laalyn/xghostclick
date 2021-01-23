#!/usr/bin/env sh

mkdir build
cd build &&
cmake ../ &&
make -j 4 &&
cd .. &&
mkdir config
ln -s build/xghostclick launch
