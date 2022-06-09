#!/bin/bash

HERE=`pwd`

### 2.1. Linux下需要安装libaio devel包

yum install libaio-devel -y

### 2.2. libfastcommon 编译安装

cd libfastcommon/
./make.sh clean && ./make.sh && ./make.sh install

cd $HERE

### 2.3. libserverframe 编译安装

cd libserverframe/
./make.sh clean && ./make.sh && ./make.sh install

cd $HERE

### 2.4. libdiskallocator 编译安装

cd libdiskallocator/
./make.sh clean && ./make.sh && ./make.sh install

cd $HERE

### 2.5. Auth client 编译安装

cd FastCFS/
./make.sh clean && ./make.sh --module=auth_client && ./make.sh --module=auth_client install

cd $HERE

### 2.6. fastDIR 编译安装

cd fastDIR/
./make.sh clean && ./make.sh && ./make.sh install
mkdir -p /etc/fastcfs/fdir/
cp conf/*.conf /etc/fastcfs/fdir/

cd $HERE

### 2.7. faststore 编译安装

cd faststore/
./make.sh clean && ./make.sh && ./make.sh install
mkdir -p /etc/fastcfs/fstore/
cp conf/*.conf /etc/fastcfs/fstore/

cd $HERE

