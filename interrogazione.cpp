#include "interrogazione.h"
#include "ui_interrogazione.h"
#include "menu.h"

Interrogazione::Interrogazione(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interrogazione)
{
    ui->setupUi(this);
    ui->Avg_daily->setVisible(true);
    ui->Avg_hour->setVisible(true);
    ui->Avg_month->setVisible(true);
    ui->Avg_week->setVisible(true);
    ui->calendarWidget->setVisible(true);
    ui->Return->setVisible(true);
}

void Interrogazione::on_Return_clicked()
{
    Menu* t = new Menu();
    t->show();
    this->close();
}

Interrogazione::~Interrogazione()
{
    delete ui;
}
