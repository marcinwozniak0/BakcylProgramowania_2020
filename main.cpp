#include "mainwindow.h"
#include <QApplication>
#include <sqlite3.h>
#include <json/value.h>

int main(int argc, char *argv[])
{
    sqlite3* _db;
    sqlite3_open(":memory:", &_db);
    Json::Value root;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
