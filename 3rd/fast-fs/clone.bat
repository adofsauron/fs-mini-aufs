
RD /s /q libfastcommon
RD /s /q libserverframe
RD /s /q libdiskallocator
RD /s /q FastCFS
RD /s /q fastDIR
RD /s /q faststore

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

cd FastCFS
RD /s /q .git
cd ..

cd fastDIR
RD /s /q .git
cd ..

cd faststore
RD /s /q .git
cd ..

pause
