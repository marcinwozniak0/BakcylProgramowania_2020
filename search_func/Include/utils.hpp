#pragma once
#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <bitset>
#include <map>


void errorHandler(int, sqlite3*);
std::string toStr(const unsigned char*);
