#include "search_flags.hpp"


searchFlags::searchFlags() : pageNr(1) {}

searchFlags::intmember::intmember() {}
searchFlags::intmember::intmember(int _val, int _min, int _max)
                                : value(_val), min(_min), max(_max) {}
