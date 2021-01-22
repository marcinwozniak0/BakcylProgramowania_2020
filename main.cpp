#include <iostream>
#include <sqlite3.h>
int main()
{
   sqlite3* _db;
   sqlite3_open("test.db", &_db);
   return 0;
}
