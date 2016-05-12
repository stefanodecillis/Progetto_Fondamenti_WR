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
#include <QThread>
#include<worker.h>

Analisi::Analisi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Analisi)
{
    ui->setupUi(this);
    setMaximumSize(681,468);//dimensione fissa
    setMinimumSize(681,468);
    timer= new QTimer(this);
    thread = new QThread();
    worker = new Worker();
    ui->loading_label->hide();
    worker->moveToThread(thread);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
    connect(worker, SIGNAL(finished()), this, SLOT(dev_giornaliere()));
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
        for(size_t i=0;i<Struttura_dati::index.size();i++){//per ogni ID utente presente
            std::vector<QDate> temp;
            bool ok = false;
            temp=get_threshold(Struttura_dati::index.at(i),ui->take_threshold->text().toDouble(&ok));
            //stampo nella cosa
            if(temp.size()==0){
                //niente.
            }else{//stampa
                for(size_t j=0;j<temp.size();j++){
                    ui->list_perdite->addItem("ID "+QString::fromStdString(Struttura_dati::index.at(i))+"  Data: "+temp[j].toString("yyyy.MM.dd"));
                }
            }
            temp.clear();
            temp.shrink_to_fit();
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

        if (consum_user[i]->get_data().tm_hour >= 6 && consum_user[i]->get_data().tm_hour <= 23)
        {
            lossFound = false;  //Se supera le ore notturne oppure cambia giorno, ripristino tutto
        }

    }

    Struttura_dati::deinit_score_ranges(consum_user); //Deinitialize
    consum_user.clear();
    return loss_consum;
}

void Analisi::devianze_mensili(Ui::Analisi *ui)
{
    // this->isTerminated=false;
    // IniziaTimer();
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
    map.clear();
    this->isTerminated=true;
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
    map.clear();
    avg_for_index.clear();
    this->isTerminated=true;
}


void Analisi::on_deviance_button_clicked()
{
    //resetto la lista
    ui->list_devianti->clear();
    if (ui->comboBox_deviance->currentText().toStdString() == "Mensile")
    {
        IniziaTimer();
        this->isTerminated=false;
        devianze_mensili(ui);
    }
    else if (ui->comboBox_deviance->currentText().toStdString() == "Settimanale")
    {
        IniziaTimer();
        this->isTerminated=false;
        devianze_settimanali(ui);
    }
    else if (ui->comboBox_deviance->currentText().toStdString() == "Giornaliera"){
        IniziaTimer();
        this->isTerminated=false;
        devianze_giornaliere(ui);
    }
}






void Analisi::devianze_giornaliere(Ui::Analisi *ui)
{
    //cancello il temporaneo nella struttura dati

    Struttura_dati::avg_for_index.clear();
    Struttura_dati::map.clear();
    worker->requestWork();
}

void Analisi::IniziaTimer()
{
    ui->loading_label->setVisible(true);
    counter=0;
    timer->start(1000);
}


void Analisi::dev_giornaliere(){

    //ottengo la media mensile complessiva
    double avg_daily = 0;
    for (size_t i = 0; i < Struttura_dati::avg_for_index.size(); i++)
    {
        avg_daily += Struttura_dati::avg_for_index[i];
    }
    avg_daily = avg_daily / Struttura_dati::avg_for_index.size();
    //stampo
    for (size_t i = 0; i< Struttura_dati::index.size(); i++)
    {
        bool devianceFound = false; //Ci servirà dopo per capire quando ha trovato l'utenza deviante
        for (size_t n = 0; n < Struttura_dati::map[Struttura_dati::index[i]].size(); n++)
        {
            if ( Struttura_dati::map.at(Struttura_dati::index[i])[n] >= (avg_daily*2) && devianceFound == false)
            {
                //fai stampare a video
                QString id = QString::fromStdString(Struttura_dati::index[i]);

                this->ui->list_devianti->addItem("ID: " + id + " Consumo giornaliero deviante!");
                //qDebug() << "ID: " + id + " Consumo giornaliero deviante!";
                devianceFound = true;
            }
        }
    }
    this->isTerminated=true;
    Struttura_dati::map.clear();
    Struttura_dati::avg_for_index.clear();
}

void Analisi::onTimeOut()
{

    if(this->isTerminated==true){
        timer->stop();
        ui->loading_label->setVisible(false);
    }else{
        if(counter%2==0){
            ui->loading_label->setText("Loading.");
        }else{
            ui->loading_label->setText("Loading..");
        }
        counter++;
    }

}
