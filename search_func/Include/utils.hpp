#pragma once
#include <sqlite3.h>
#include <iostream>


void errorHandler(int, sqlite3*);
std::string toStr(const unsigned char*);
