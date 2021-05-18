#include "ErrorWindow.h"

#include <QMessageBox>

ErrorWindow::ErrorWindow(std::string message)
{
    QMessageBox messageBox;
    messageBox.setWindowTitle("Try another card");
    messageBox.setText(QString::fromStdString(message));
    messageBox.exec();
}
