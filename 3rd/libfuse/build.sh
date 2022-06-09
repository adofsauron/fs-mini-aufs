#!/bin/bash

pip3 install meson ninja

rm build -rf
mkdir build/; 
cd build
meson ..
meson configure -D prefix=/usr
meson configure -D examples=true
ninja && ninja install
sed -i 's/#user_allow_other/user_allow_other/g' /etc/fuse.conf

cd -
