#include "mainwindow.h"

#include <QApplication>
#include "Logger.hpp"

int main()
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
