#pragma once

#include <QDialog>

#include "DeckBuilder/Include/DeckBuilder.hpp"

namespace Ui {
class DeckWindow;
}

class DeckWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DeckWindow( DeckBuilder* deck, QWidget *parent = nullptr);
    ~DeckWindow();

private:
    Ui::DeckWindow *ui;
};


