#include "mainwindow.h"
#include "filedownloader.h"

#include <QApplication>
#include <sqlite3.h>
#include <json/value.h>

int main(int argc, char *argv[])
{
    sqlite3* _db;
    sqlite3_open(":memory:", &_db);
    Json::Value root;
    
    fd::FileDownloader testRun("data");
    std::string links_[] = {"https://dd.b.pvp.net/latest/core/en_us/data/globals-en_us.json", 
                            "https://dd.b.pvp.net/latest/set1/en_us/data/set1-en_us.json", 
                            "https://dd.b.pvp.net/latest/set2/en_us/data/set2-en_us.json", 
                            "https://dd.b.pvp.net/latest/set3/en_us/data/set3-en_us.json", 
                            "https://dd.b.pvp.net/latest/set4/en_us/data/set4-en_us.json"};
    std::string fileNames_[] = {"globals-en_us.json", 
                                "set1-en_us.json", 
                                "set2-en_us.json", 
                                "set3-en_us.json", 
                                "set4-en_us.json"};
    testRun.addLinks(links_, fileNames_, (sizeof(links_)/sizeof(links_[0])));
    testRun.download();
    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
