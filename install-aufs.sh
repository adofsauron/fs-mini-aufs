#!/bin/bash

cd aufs

if [ "0" != `lsmod | grep aufs | wc -l` ]; then
    echo rmmod aufs
    rmmod aufs
fi

echo insmod aufs.ko
insmod aufs.ko

lsmod | grep aufs

cd -