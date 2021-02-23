#!/bin/bash
if [[ ! -f /usr/include/sqlite3.h ]]
then
    curl https://sqlite.org/2021/sqlite-autoconf-3340100.tar.gz -o "/usr/include/sqlite.tar.gz"
fi
if [[ ! -d /usr/include/jsoncpp/json ]]
then
    curl https://raw.githubusercontent.com/open-source-parsers/jsoncpp/1.9.4/include/json/{allocator.h, value.h, assertions.h, config.h, forwards.h, json.h, json_features.h, reader.h, version.h, writer.h} -o /usr/include/jsoncpp/json/#1
    # curl https://raw.githubusercontent.com/open-source-parsers/jsoncpp/1.9.4/src/lib_json/json_tool.h -o /usr/include/jsoncpp/json/json_value.h
    # curl https://raw.githubusercontent.com/open-source-parsers/jsoncpp/1.9.4/src/lib_json/json_reader.cpp -o /usr/include/jsoncpp/json/json_reader.cpp
    # curl https://raw.githubusercontent.com/open-source-parsers/jsoncpp/1.9.4/src/lib_json/json_writer.cpp -o /usr/include/jsoncpp/json/json_writer.cpp
    # curl https://raw.githubusercontent.com/open-source-parsers/jsoncpp/1.9.4/src/lib_json/json_value.cpp
fi
if [[ ! -d /usr/lib/qt5/bin ]]
then
    sudo apt-get install qt5-default
fi