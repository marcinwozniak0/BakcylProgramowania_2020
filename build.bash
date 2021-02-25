#!/bin/bash
if [[ ! -f /usr/include/sqlite3.h ]]
then
    curl https://sqlite.org/2021/sqlite-autoconf-3340100.tar.gz -o "/usr/include/sqlite.tar.gz"
    tar -zxvf /usr/include/sqlite.tar.gz /usr/include/sqlite/
fi
if [[ ! -d /usr/include/jsoncpp/json ]]
then
    CURRENTDIR=pwd
    cd /usr/include/
    mkdir jsoncpp
    cd jsoncpp
    mkdir json
    curl https://raw.githubusercontent.com/open-source-parsers/jsoncpp/1.9.4/include/json/{allocator.h, value.h, assertions.h, config.h, forwards.h, json.h, json_features.h, reader.h, version.h, writer.h} -o #1
    cd CURRENTDIR
fi
if [[ ! -d /usr/lib/qt5/bin ]]
then
    sudo apt-get install qt5-default
fi