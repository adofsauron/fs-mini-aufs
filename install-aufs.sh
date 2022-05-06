#!/bin/bash

cd aufs

insmod aufs.ko

lsmod | grep aufs

cd -