#!/bin/bash
if [[ ! -f /usr/include/sqlite3.h ]]
then
    sudo apt-get install libsqlite3-dev
fi
if [[ ! -f /usr/include/jsoncpp/json/json.h ]]
then
    sudo apt-get install libjsoncpp-dev
fi
if [[ ! -d /usr/lib/qt5/bin ]]
then
    sudo apt-get install qt5-default
fi