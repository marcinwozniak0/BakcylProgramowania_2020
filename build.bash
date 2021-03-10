#!/bin/bash
CURRENTDIR=$(pwd)
if [[ ! -f /usr/include/sqlite3.h ]]
then
    cd /usr/include
    touch sqlite.tar.gz
    mkdir sqlite
    curl https://sqlite.org/2021/sqlite-autoconf-3340100.tar.gz -o sqlite.tar.gz
    tar -zxvf sqlite.tar.gz sqlite
    cd sqlite
    ./configure
    make
    ar -rcs sqlite3.a sqlite3-shell.o sqlite3.o sqlite3-sqlite3.o
    make install
fi
if [[ ! -d /usr/include/jsoncpp/json ]]
then
    cd /usr/include/
    mkdir jsoncpp
    cd jsoncpp
    mkdir json
    curl https://raw.githubusercontent.com/open-source-parsers/jsoncpp/1.9.4/include/json/{allocator.h, value.h, assertions.h, config.h, forwards.h, json.h, json_features.h, reader.h, version.h, writer.h} -o #1
fi
if [[ ! -d /usr/lib/qt5/bin ]]
then
    cd /usr/lib
    mkdir qt5
    cd qt5
    mkdir bin
    cd bin
    touch qt-opensource-linux-x64-5.12.4.run
    curl https://download.qt.io/archive/qt/5.12/5.12.4/qt-opensource-linux-x64-5.12.4.run -o qt-opensource-linux-x64-5.12.4.run
    chmod +x qt-opensource-linux-x64-5.12.4.run
    ./qt-opensource-linux-x64-5.12.4.run
fi

cd $CURRENTDIR