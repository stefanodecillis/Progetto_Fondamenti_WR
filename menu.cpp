#include "menu.h"
#include "ui_menu.h"
#include<visualizzaione.h>
#include<struttura_dati.h>
#include<qmessagebox.h>
#include<input_file.h>
#include <interrogazione.h>



Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
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
void Menu::setValue(QString str){ //stampa quello passato dal sender, qui esplicito un nome della variabile
    QMessageBox msgBox;
   Struttura_dati::FilePath =str;//salvo nella classe con membri static
    msgBox.setText(str);//vedo url pasato
    msgBox.exec();
    //poi riempio la mappa
    input_file::read_file(Struttura_dati::Wreading,Struttura_dati::FilePath.toStdString());
// mi salvo gli id presenti nella mappa*
std::vector<std::string>indici;
 for(auto i: Struttura_dati::Wreading){
    indici.push_back(i.first);
 }
 Struttura_dati::index=indici;//mi tengo copia dei codici cliente presenti.*
}

void Menu::on_button2_clicked()//visualizzazione
{
    Interrogazione* t= new Interrogazione();//apro la nuova form di vusalizzazione e chiudo la corrente
    t->show();
    this->close();
}
