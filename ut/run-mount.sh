#!/bin/bash

mkdir -p /au

mount -t aufs none /au

tree /au
