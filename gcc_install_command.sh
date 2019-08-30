#!/bin/sh

wget http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-9.2.0/gcc-9.2.0.tar.gz
tar xvzf gcc-9.2.0.tar.gz
cd gcc-9.2.0
./contrib/download_prerequisites
./configure --enable-languages=c,c++ --prefix=/usr/local/lib/gcc-9.2.0 --disable-bootstrap --disable-multilib
make
make install
