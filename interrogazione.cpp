#include "interrogazione.h"
#include "ui_interrogazione.h"
#include "menu.h"
#include<qdebug.h>
#include<qmessagebox.h>

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
    ui->calendarWidget->setGridVisible(true);
    ui->calendarWidget->setMinimumDate(QDate(2015, 1, 1));
    ui->calendarWidget->setMaximumDate(QDate(2015, 12, 31));
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

void Interrogazione::on_calendarWidget_clicked(const QDate &date)
{
    //valori selezione dal calendario
    QMessageBox msgBox;
    msgBox.setText(QString::number(date.year()));//date.year, date.month, date.day.. restituiscono interi
    msgBox.exec();
    msgBox.setText(QString::number(date.month()));
    msgBox.exec();
    msgBox.setText(QString::number(date.day()));
    msgBox.exec();

qDebug()<<date;
}
