#!/bin/bash

dos2unix *.sh
chmod +x *.sh

dos2unix build-aux/*
chmod +x build-aux/*

bash autogen.sh

./configure

make clean
make -j"$(nproc)"

