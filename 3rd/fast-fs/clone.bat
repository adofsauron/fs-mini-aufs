
RD /s /q libfastcommon
RD /s /q libserverframe
RD /s /q libdiskallocator
RD /s /q fastcfs
RD /s /q fastdir
RD /s /q faststore


git rm -rf libfastcommon
git rm -rf libserverframe
git rm -rf libdiskallocator
git rm -rf fastcfs
git rm -rf fastdir
git rm -rf faststore

git config --global core.autocrlf false

git clone https://gitee.com/fastdfs100/libfastcommon.git

git clone https://gitee.com/fastdfs100/libserverframe.git

git clone https://gitee.com/fastdfs100/libdiskallocator.git

git clone https://gitee.com/fastdfs100/FastCFS.git

git clone https://gitee.com/fastdfs100/fastDIR.git

git clone https://gitee.com/fastdfs100/faststore.git

cd libfastcommon
RD /s /q .git
cd ..

cd libserverframe
RD /s /q .git
cd ..

cd libdiskallocator
RD /s /q .git
cd ..

cd fastcfs
RD /s /q .git
cd ..

cd fastdir
RD /s /q .git
cd ..

cd faststore
RD /s /q .git
cd ..

pause
