#/bin/bash
#Cornball Install Script
gksudo apt-get install cmake libpcre3-dev zlib1g-dev libgcrypt11-dev libicu-dev python
mkdir cornball
cd cornball
mkdir cppcms
cd cppcms
wget -O cppcms.tar.bz2 "http://downloads.sourceforge.net/project/cppcms/cppcms/1.0.5/cppcms-1.0.5.tar.bz2?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fcppcms%2Ffiles%2F&ts=1436190659&use_mirror=iweb"
tar -xjf cppcms.tar.bz2
cd cppcms
cmake
make
make test
gksudo make install
cd ../..
wget https://github.com/FlamingSpork/cornball-fms/archive/master.zip
unzip master.zip
cd cornball-fms-master
make fms
