#include "menu.h"
#include "ui_menu.h"
#include<visualizzaione.h>
#include<struttura_dati.h>
#include<qmessagebox.h>
#include<input_file.h>
#include <interrogazione.h>
#include <analisi.h>
#include <QThread>
#include<worker.h>
#include<qdebug.h>
#include<drag_drop.h>



Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    thread = new QThread();
    worker = new Worker();
    worker->moveToThread(thread);
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);

}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_button1_clicked()//visualizzazione
{
    visualizzaione* t= new visualizzaione();//apro la nuova form di vusalizzazione e chiudo la corrente
    t->show();
    this->close();
}



void Menu::on_button2_clicked()//visualizzazione
{
    Interrogazione* t= new Interrogazione();//apro la nuova form di vusalizzazione e chiudo la corrente
    t->show();
    this->close();
}

void Menu::on_button3_clicked()
{
    Analisi* t = new Analisi(); //apro analisi
    t->show();
    this->close();
}
