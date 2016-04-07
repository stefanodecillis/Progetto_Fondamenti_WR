#include "analisi.h"
#include "ui_analisi.h"
#include <menu.h>
#include <iostream>

Analisi::Analisi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Analisi)
{
    ui->setupUi(this);
}

Analisi::~Analisi()
{
    delete ui;
}

void Analisi::on_exit_button_clicked()
{
    Menu* t = new Menu();
    std::cout << "BOOHM";
    t->show();
    this->close();
}
