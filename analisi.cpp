#include "analisi.h"
#include "ui_analisi.h"
#include <menu.h>
#include <vector>
#include <QDate>
#include <struttura_dati.h>
#include <water_reading.h>
#include <qstring.h>
#include <qdebug.h>
#include <visualizzaione.h>

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

//devianze_mensili(ui);


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

void Analisi::devianze_mensili(Ui::Analisi *ui)
{
    std::map<std::string, std::vector<double>> map;
    std::vector<double> avg_for_index;    //salvo tutte le medie di tutte le utenze
    for (size_t i = 0; i < Struttura_dati::index.size(); i++)
    {
        std::vector<double> consum_monthly = visualizzaione::Consumo_tot_per_month(Struttura_dati::index[i]); //acquisto i valori
        //salvo nella mappa
        map[Struttura_dati::index[i]] = consum_monthly;
        //mi salvo la media di questo utente
        double avg = 0;
        for (size_t n = 0; n < consum_monthly.size(); n++)
        {
            avg += consum_monthly[n];
        }
        avg = avg / consum_monthly.size();
        avg_for_index.push_back(avg);
    }
    //ottengo la media mensile complessiva
    double avg_monthly = 0;
    for (size_t i = 0; i < avg_for_index.size(); i++)
    {
      avg_monthly += avg_for_index[i];
    }
    avg_monthly = avg_monthly / avg_for_index.size();
    //stampo
    for (size_t i = 0; i< Struttura_dati::index.size(); i++)
    {
    bool devianceFound = false;
        for (size_t n = 0; n < map[Struttura_dati::index[i]].size(); n++)
        {
            if ( map.at(Struttura_dati::index[i])[n] >= (avg_monthly*2) && devianceFound == false)
            {
                //fai stampare a video
                QString id = QString::fromStdString(Struttura_dati::index[i]);
                ui->list_devianti->addItem("ID: " + id + " consumo deviante mensile");
                devianceFound = true;
            }
        }
    }
}


void Analisi::devianze_settimanali(Ui::Analisi *ui)
{
    std::map<std::string, std::vector<double>> map;
    std::vector<double> avg_for_index;    //salvo tutte le medie di tutte le utenze
    for (std::pair<std::string,std::vector<water_reading*>> x: Struttura_dati::Wreading)
    {
       map[x.first];
        for (int month = 1; month <= 12; month++)
        {
            std::vector<double> consum_weekly = visualizzaione::weekly(x.first,month); //acquisto i valori
            //salvo nella mappa
            //mi salvo la media di questo utente
            double avg = 0;
            for (size_t n = 0; n < consum_weekly.size(); n++)
            {
               map.at(x.first).push_back(consum_weekly[n]);
                avg += consum_weekly[n];
            }
            avg = avg / consum_weekly.size();
            avg_for_index.push_back(avg);
        }
    }
    //ottengo la media mensile complessiva
    double avg_weekly = 0;
    for (size_t i = 0; i < avg_for_index.size(); i++)
    {
      avg_weekly += avg_for_index[i];
    }
    avg_weekly = avg_weekly / avg_for_index.size();
    //stampo
    for (size_t i = 0; i< Struttura_dati::index.size(); i++)
    {
        bool devianceFound = false; //Ci servirà dopo per capire quando ha trovato l'utenza deviante
        for (size_t n = 0; n < map[Struttura_dati::index[i]].size(); n++)
        {
            if ( map.at(Struttura_dati::index[i])[n] >= (avg_weekly*2) && devianceFound == false)
            {
                //fai stampare a video
                QString id = QString::fromStdString(Struttura_dati::index[i]);
                ui->list_devianti->addItem("ID: " + id + " Consumo settimanale deviante!");
                devianceFound = true;
            }
        }
    }
}


void Analisi::on_deviance_button_clicked()
{
    //resetto la lista
    ui->list_devianti->clear();
    if (ui->comboBox_deviance->currentText().toStdString() == "Mensile")
    {
    devianze_mensili(ui);
    }
    else if (ui->comboBox_deviance->currentText().toStdString() == "Settimanale")
    {
    devianze_settimanali(ui);
    }
    else if (ui->comboBox_deviance->currentText().toStdString() == "Giornaliera")
    devianze_giornaliere(ui);
}

void Analisi::devianze_giornaliere(Ui::Analisi *ui)
{
    std::map<std::string, std::vector<double>> map;
    std::vector<double> avg_for_index;    //salvo tutte le medie di tutte le utenze
    for (std::pair<std::string,std::vector<water_reading*>> x: Struttura_dati::Wreading)
    {
       map[x.first];
        for (int month = 1; month <= 12; month++)
        {
            int day_count = 0;
            switch(month)
            {
            case 1 : case 3 : case 5 :  case 7 : case 8 : case 10 : case 12:
                day_count = 31;
                break;
            case 2:
                day_count = 28;
                break;
            case 4: case 6 : case 9 : case 11 :
                day_count = 30;
                break;
            default:
                day_count = 30;
            }
            for (int day = 1; day <= day_count; day++)
            {
                std::vector<double> consum_daily = visualizzaione::daily(month,day,x.first); //acquisto i valori
                //salvo nella mappa
                //mi salvo la media di questo utente
                double avg = 0;
                for (size_t n = 0; n < consum_daily.size(); n++)
                {
                    map.at(x.first).push_back(consum_daily[n]);
                    avg += consum_daily[n];
                }
                avg = avg / consum_daily.size();
                avg_for_index.push_back(avg);qDebug() << "STEP 1";
            }
        }
    }
    //ottengo la media mensile complessiva
    double avg_weekly = 0;
    for (size_t i = 0; i < avg_for_index.size(); i++)
    {
      avg_weekly += avg_for_index[i];
    }
    avg_weekly = avg_weekly / avg_for_index.size();
    //stampo
    for (size_t i = 0; i< Struttura_dati::index.size(); i++)
    {
        bool devianceFound = false; //Ci servirà dopo per capire quando ha trovato l'utenza deviante
        for (size_t n = 0; n < map[Struttura_dati::index[i]].size(); n++)
        {
            if ( map.at(Struttura_dati::index[i])[n] >= (avg_weekly*2) && devianceFound == false)
            {
                //fai stampare a video
                QString id = QString::fromStdString(Struttura_dati::index[i]);
                ui->list_devianti->addItem("ID: " + id + " Consumo giornaliero deviante!");
                devianceFound = true;
            }
        }
    }
}
