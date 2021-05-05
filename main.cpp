#include "MainWindow.h"

#include <QApplication>
#include <sqlite3.h>
#include <json/value.h>

int main(int argc, char *argv[])
{
    sqlite3* _db;
    sqlite3_open(":memory:", &_db);
    Json::Value root;
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("../../BakcylProgramowania_2020/source/icon.png"));
    MainWindow w;
    w.show();

    sqlite3_close(_db);
    return a.exec();
}
