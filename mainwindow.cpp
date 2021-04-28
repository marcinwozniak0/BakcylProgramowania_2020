#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QRegularExpression>

#include "searchrequest.h"


constexpr size_t windowWightInPx = 1200;
constexpr size_t windowHeightInPx = 800;

void centerWindow(QWidget *widget);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Options->setCurrentIndex(0);

    setFixedSize(windowWightInPx,windowHeightInPx);
    centerWindow(this);

    this->setWindowTitle("Deckbuilder");

    cardContainer = new CardsContainer(ui->Cards);
    for(auto& it : cardContainer->getCards()){
        connect(it, &QPushButton::clicked, this, &MainWindow::cardClicked);
    }

}
MainWindow::~MainWindow()
{
    delete ui;
    delete cardContainer;
}


void MainWindow::on_Search_B_clicked(){

    SearchRequest request(ui->HealthFrom->text().toStdString(),
                          ui->HealthTo->text().toStdString(),

                          ui->CostFrom->text().toStdString(),
                          ui->CostTo->text().toStdString(),


                          ui->AttackFrom->text().toStdString(),
                          ui->AttackTo->text().toStdString(),

                          ui->Name_T->text().toStdString(),
                          convertCheckbox("Rarity_?"),
                          convertCheckbox("Typ_?"),
                          convertCheckbox("Region_??"));

    request.ShowRequest();

}
std::vector<std::string> MainWindow::convertCheckbox(std::string regex){
    QRegularExpression chexbox_regex(regex.c_str());
    std::vector<std::string> checkboxNames;

    for(auto& it : ui->OptionsAndDeck->findChildren<QCheckBox*>(chexbox_regex)){
        if(it->isChecked()){
                checkboxNames.push_back(it->text().toUtf8().constData());
        }
    }
    return checkboxNames;
}
void MainWindow::cardClicked(){
    QPushButton *button = (QPushButton *)sender();
    displayCardWindow(button->property("Id").toUInt());

}
void MainWindow::displayCardWindow(unsigned int cardId){
    CardWindow cardWindow(cardId, ui->OptionsAndDeck->findChild<QLabel*>("DeckDisplay"), &deckbuilder, this);
    cardWindow.setModal(true);
    cardWindow.exec();
}

void centerWindow(QWidget *widget){

    int x, y;
    int screenWidth;
    int screenHeight;

    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();


    x = (screenWidth - windowWightInPx) / 2;
    y = (screenHeight - windowHeightInPx) / 2;

    widget->setGeometry(x,y,windowWightInPx,windowHeightInPx);

}



void MainWindow::on_Health_B_clicked()
{
    ui->Options->setCurrentIndex(1);
}

void MainWindow::on_Cost_B_clicked()
{
     ui->Options->setCurrentIndex(2);
}

void MainWindow::on_Attack_B_clicked()
{
     ui->Options->setCurrentIndex(3);
}

void MainWindow::on_Type_B_clicked()
{
     ui->Options->setCurrentIndex(4);
}

void MainWindow::on_Rarity_B_clicked()
{
     ui->Options->setCurrentIndex(5);
}

void MainWindow::on_Region_B_clicked()
{
     ui->Options->setCurrentIndex(6);
}


void MainWindow::on_GoNext_B_clicked()
{
    int page = ui->NumberOfPage->text().toInt();
    if(page < 1){
        ui->NumberOfPage->setText("1");
    }else{
        ui->NumberOfPage->setText(QString::number(++page));
    }
}

void MainWindow::on_GoBack_B_clicked()
{
    int page = ui->NumberOfPage->text().toInt();
    if(page > 1){
        ui->NumberOfPage->setText(QString::number(--page));
    }
}
