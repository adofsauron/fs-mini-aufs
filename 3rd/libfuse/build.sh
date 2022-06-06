#!/bin/bash

pip3 install meson ninja

rm build -rf
meson setup build

cd build
ninja
ninja install

cd -
