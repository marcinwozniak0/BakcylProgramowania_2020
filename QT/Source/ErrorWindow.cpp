#include "ErrorWindow.h"

#include <QMessageBox>

ErrorWindow::ErrorWindow(std::string message)
{
    QMessageBox messageBox;
    messageBox.setText(QString::fromStdString(message));
    messageBox.exec();
}
