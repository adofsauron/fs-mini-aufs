#!/bin/bash

rm build -rf
mkdir -p build

cd build

cmake ..

make -j"$(nproc)"
make install

cd -
