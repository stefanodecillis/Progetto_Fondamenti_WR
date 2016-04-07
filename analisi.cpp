#include "analisi.h"
#include "ui_analisi.h"
#include <menu.h>
#include <vector>
#include <QDate>
#include <struttura_dati.h>
#include<qstring.h>
#include<qdebug.h>

Analisi::Analisi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Analisi)
{
    ui->setupUi(this);
    setMaximumSize(681,468);//dimensione fissa
    setMinimumSize(681,468);
}

Analisi::~Analisi()
{
    delete ui;
}

void Analisi::on_exit_button_clicked()
{
    Menu* t = new Menu();
    t->show();
    this->close();
}

void Analisi::on_button_dati_clicked()
{
   if (!(ui->take_threshold->text().isEmpty())) //Se non è vuota
   {
       //resetto le qlist
       ui->list_perdite->clear();


       //Lavora

       for(int i=0;i<Struttura_dati::index.size();i++){//per ogni ID utente presente
        std::vector<QDate> temp;
        bool ok = false;

        temp=get_threshold(Struttura_dati::index.at(i),ui->take_threshold->text().toDouble(&ok));
        std::string temp2=Struttura_dati::index.at(i);
        //stampo nella cosa
        if(temp.size()==0){
            //niente.
        }else{//stampa
        for(int i=0;i<temp.size();i++){
//ui->list_devianti->addItem(QString::fromStdString(temp2));
ui->list_perdite->addItem(QString::fromStdString("ID ")+QString::fromStdString(temp2)+"  Data: "+temp[i].toString("yyyy.MM.dd"));
}
        }

       }

   }//fine if principale
}

std::vector<QDate> Analisi::get_threshold(std::string user, double threshold)
{


    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);   //Sorting
    std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));   //Acquisto vettore letture
    std::vector<QDate> loss_consum;   //inizializzo vector che conterra le date dei consumi
    bool lossFound = false;
    for (size_t i = 0; i < consum_user.size(); i++)
    {
        if ((consum_user[i]->get_data().tm_hour >= 0 && consum_user[i]->get_data().tm_hour <= 5) && lossFound == false)  //Se è compreso tra le 00.00 e le 05.00
        {

            if (consum_user[i]->get_consumption() >= threshold)
            {

                lossFound = true;
                QDate data(consum_user[i]->get_data().tm_year,consum_user[i]->get_data().tm_mon,consum_user[i]->get_data().tm_mday); //creo QDate

                loss_consum.push_back(data); //inserisco QDate nel vector
            }
        }
        //if ((consum_user[i]->get_data().tm_hour >= 6 && consum_user[i]->get_data().tm_hour <= 23) )
        if (consum_user[i]->get_data().tm_hour >= 6 && consum_user[i]->get_data().tm_hour <= 23)
        {

           // && consum_user[i]->get_data().tm_mday != consum_user[i+1]->get_data().tm_mday
            lossFound = false;  //Se supera le ore notturne oppure cambia giorno, ripristino tutto
        }
    }

  return loss_consum;
}
