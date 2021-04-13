#pragma once
#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <bitset>
#include <map>


void errorHandler(int, sqlite3*);
std::string toStr(const unsigned char*);

template<int size>
std::vector<std::string> bitsetToVec(std::bitset<size>, std::string);
