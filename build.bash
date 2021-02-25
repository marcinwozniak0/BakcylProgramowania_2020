#!/bin/bash
CURRENTDIR=pwd
if [[ ! -f /usr/include/sqlite3.h ]]
then
    cd /usr/include
    touch sqlite.tar.gz
    mkdir sqlite
    curl https://sqlite.org/2021/sqlite-autoconf-3340100.tar.gz -o sqlite.tar.gz
    tar -zxvf sqlite.tar.gz sqlite
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
    sudo apt-get install qt5-default
fi

cd CURRENTDIR