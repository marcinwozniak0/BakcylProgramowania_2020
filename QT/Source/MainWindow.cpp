#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QRegularExpression>

#include "DeckWindow.h"


const std::string dataBaseParth = "database.sql";
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

    cardContainer = std::make_unique<CardsContainer>(ui->Cards);
    for(auto& it : cardContainer->getCards()){
        connect(it, &QPushButton::clicked, this, &MainWindow::cardClicked);
    }

    currentRequest = std::make_unique<CardApi::Filters>();

    dataBase = SqliteHelper::open_db(dataBaseParth.c_str());
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Search_B_clicked(){

    currentRequest->minHealth = ui->HealthFrom->text().toInt();
    currentRequest->maxHealth = ui->HealthTo->text().toInt();

    currentRequest->minCost = ui->CostFrom->text().toInt();
    currentRequest->maxCost = ui->CostTo->text().toInt();

    currentRequest->minAttack = ui->AttackFrom->text().toInt();
    currentRequest->maxAttack = ui->AttackTo->text().toInt();

    currentRequest->cardName = ui->Name_T->text().toStdString();

    currentRequest->rarityNames = convertCheckbox("Rarity_?");
    //currentRequest->cardType_ = convertCheckbox("Typ_?"); //TODO
    currentRequest->regionNames = convertCheckbox("Region_??");
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
    displayCardWindow(button->property("Id").toString().toStdString());

}
void MainWindow::displayCardWindow(std::string cardId){
    CardWindow cardWindow(cardId, ui->OptionsAndDeck->findChild<QLabel*>("DeckDisplay"), &deckbuilder, &dataBase, this);
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
        ui->NumberOfPage->setText("2");
        currentRequest->setPage(2);
    }else{
        ui->NumberOfPage->setText(QString::number(++page));
        currentRequest->setPage(page);
    }

}

void MainWindow::on_GoBack_B_clicked()
{
    int page = ui->NumberOfPage->text().toInt();
    if(page > 1){
        ui->NumberOfPage->setText(QString::number(--page));
        currentRequest->setPage(page);
    }
}


void MainWindow::on_NumberOfPage_editingFinished()
{
    currentRequest->setPage(ui->NumberOfPage->text().toInt());
}

void MainWindow::on_pushButton_clicked()
{   
        this->hide();
        DeckWindow deckWindow(&deckbuilder,this->geometry() ,this);
        deckWindow.setModal(true);
        deckWindow.exec();
        deckWindow.deleteLater();
        this->show();
}