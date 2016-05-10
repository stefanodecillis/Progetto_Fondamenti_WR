#include "interrogazione.h"
#include "ui_interrogazione.h"
#include "menu.h"
#include<qdebug.h>
#include<qmessagebox.h>
#include<struttura_dati.h>
#include <water_reading.h>
#include <iostream>
#include<QDate>

Interrogazione::Interrogazione(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interrogazione)
{
    ui->setupUi(this);
    setMaximumSize(714,505);//dimensione fissa
    setMinimumSize(714,505);
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


    //faccio il controllo se la prima data è minore della seconda
    if(count==0){
        this->date1=date;
        QString temp;
        temp=QString::number(date1.year());
        temp+="-"+QString::number(date1.month());
        temp+="-"+QString::number(date1.day());
        ui->data1->setText(temp);
        count++;
    }else if(count==1){ //faccio il controllo se la prima data è minore della seconda
        if(date1>date){//errore selezione dato..rifalla
            QMessageBox msgBox;
            msgBox.setText("Errore! Data2<Data1");
            msgBox.exec();
        }else{
            this->date2=date;
            QString temp2;
            temp2=QString::number(date2.year());
            temp2+="-"+QString::number(date2.month());
            temp2+="-"+QString::number(date2.day());
            ui->data2->setText(temp2);
            count++;
        }
    }else{
        //non inserisco piu dati..fino alla prossima interrogazione

        QMessageBox msgBox;
        msgBox.setText("Per Inserire un nuovo intervallo, fare Reset");//ricordo di settare il contatore
        msgBox.exec();
    }

}

void Interrogazione::on_Find_user_editingFinished()
{
    //controlla se l'id specificato esiste o meno
    for(size_t i=0;i<Struttura_dati::index.size();i++){
        QString nuova=QString::fromStdString(Struttura_dati::index.at(i));
        if(ui->Find_user->text()==nuova){
            input_codice_cliente=true;
            ui->Find_user->setStyleSheet("QLineEdit{border:2px solid green;}");
            //qDebug()<<nuova;
            return ;
        }
    }
    //se non esiste non faccio nemmeno la ricerca..meglio dare messaggio di avviso
    input_codice_cliente=false;
    ui->Find_user->setStyleSheet("QLineEdit{border:2px solid red;}");
}

void Interrogazione::on_Reset_clicked()
{
    this->count=0;
    ui->data1->setText("");
    ui->data2->setText("");
    QDate null1;
    QDate null2;
    this->date1=null1;
    this->date2=null2;

}

void Interrogazione::on_Find_clicked()
{
    //se il dato input è valido e le date sono valide
    if(this->input_codice_cliente==true&&this->date1.isValid()&&this->date2.isValid()){

        QDate data1 = this->date1;

        QDate data2 = this->date2;

        QString mc = " m³";
        int diff = data1.daysTo(data2);  //conosco i giorni di distanza tra le due date
        double totalcons = total_consumption(data1,data2,ui->Find_user->text().toStdString());
        double avg_hour = avg_hourly(data1,data2,ui->Find_user->text().toStdString());    //inizializzo media oraria e totale poiché le avremo in ogni caso
        ui->setHere_hour->setText(QString::number(avg_hour) + mc);
        ui->setHere_tot->setText(QString::number(totalcons) + mc);
        if(diff > 0)   //Se abbiamo piu di un giorno, dobbiamo inserire una media giornaliera
        {
         double daily = avg_daily(data1,data2,ui->Find_user->text().toStdString());
         ui->setHere_daily->show();
         ui->Avg_daily->show();
         ui->setHere_daily->setText(QString::number(daily) + mc);
        }
        else {
            ui->setHere_daily->hide();   //Nascondo nel caso non mi servano
            ui->Avg_daily->hide();
        }
        if(diff >= 7)
        {
            double weekly = avg_weekly(data1,data2,ui->Find_user->text().toStdString());
            ui->Avg_week->show();
            ui->setHere_week->show();
            ui->setHere_week->setText(QString::number(weekly) + mc);
        }
        else
        {
            ui->setHere_week->hide();
            ui->Avg_week->hide();
        }
        if (diff > 30)
        {
            double monthly = avg_monthly(data1,data2,ui->Find_user->text().toStdString());
            ui->setHere_month->show();
            ui->Avg_month->show();
            ui->setHere_month->setText(QString::number(monthly) + mc);
        }
        else
        {
            ui->setHere_month->hide();
            ui->Avg_month->hide();
        }
    }else{
        QMessageBox msgBox;
        msgBox.setText("DATI NON VALIDI");//non ho id e data corretta
        msgBox.exec();
    }
}

double Interrogazione::total_consumption (QDate data1, QDate data2,std::string user)
{
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);
    std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));
    std::vector<double> values;

    for (size_t i = 0; i < consum_user.size(); i++)
    {
        //Inserisco i valori compresi tra le due date
        QDate nuovo(consum_user[i]->get_data().tm_year,consum_user[i]->get_data().tm_mon,consum_user[i]->get_data().tm_mday);
     if(data1<=nuovo && data2>=nuovo){
     values.push_back(consum_user[i]->get_consumption());
     }
}
    Struttura_dati::deinit_score_ranges(consum_user);
    consum_user.clear();
    if (values.size() == 0)
    {
        //Non ci sono letture questo utente
        return 0;
    }
    double total_consumption=0;
    for (size_t i = 0; i<values.size(); i++)
    {
        total_consumption += values[i];
    }


return total_consumption;
}


double Interrogazione::avg_hourly (QDate data1, QDate data2, std::string user)
{
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);
    std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));

    std::vector<double> values;


    for (size_t i = 0; i < consum_user.size(); i++)
    {
        //Inserisco i valori compresi tra le due date
        QDate nuovo(consum_user[i]->get_data().tm_year,consum_user[i]->get_data().tm_mon,consum_user[i]->get_data().tm_mday);
        if(data1<=nuovo && data2>=nuovo){
            values.push_back(consum_user[i]->get_consumption());
        }
    }
Struttura_dati::deinit_score_ranges(consum_user);
consum_user.clear();
    if (values.size() == 0)
    {
        //Se non ha valori, torna nulla
        return 0;
    }

    double avg_hourly = values[0];

    for (size_t i = 1; i<values.size(); i++)
    {
        avg_hourly += values[i];
    }
   avg_hourly= avg_hourly/values.size();


return avg_hourly;
}

double Interrogazione::avg_daily (QDate data1, QDate data2, std::string user)
{
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);
    std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));   //ordino il vettore consumi nella mappa

    double avg_daily = 0;     //variabile di apppoggio consumi
    int diff=data1.daysTo(data2) + 1; //Esempio: se ci troviamo nello stesso giorno, dobbiamo poter dividere per uno mentre se sono due giorni, il numero da dividere sarà due e non uno



    for (size_t i = 0; i < consum_user.size(); i++)
    {
        QDate currentdate(consum_user[i]->get_data().tm_year,consum_user[i]->get_data().tm_mon,consum_user[i]->get_data().tm_mday);

        if(data1<=currentdate && data2>=currentdate){

           avg_daily+=consum_user[i]->get_consumption();
        }

    }
   Struttura_dati::deinit_score_ranges(consum_user);
   consum_user.clear();
    if(avg_daily == 0)
    {
        //Se è uguale a zero, ritorna zero
        return 0;
    }

return (avg_daily=avg_daily/diff);
}

double Interrogazione::avg_weekly (QDate data1,QDate data2, std::string user)
{
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);
    std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));   //ordino il vettore consumi nella mappa

    double avg_weekly = 0;     //variabile di apppoggio consumi
    int diff=data1.daysTo(data2) + 1;  //differenza giorni tra le due date
    diff = diff / 7;  //trovo numero settimane



    for (size_t i = 0; i < consum_user.size(); i++)
    {
        QDate currentdate(consum_user[i]->get_data().tm_year,consum_user[i]->get_data().tm_mon,consum_user[i]->get_data().tm_mday);

        if(data1<=currentdate && data2>=currentdate){

           avg_weekly+=consum_user[i]->get_consumption();
        }

    }

    Struttura_dati::deinit_score_ranges(consum_user);
    consum_user.clear();

    if(avg_weekly == 0)
    {
        //Se è uguale a zero, ritorna zero
        return 0;
    }

return (avg_weekly=avg_weekly/diff);
}

double Interrogazione::avg_monthly (QDate data1,QDate data2, std::string user)
{
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);
    std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));   //ordino il vettore consumi nella mappa

    double avg_month = 0;     //variabile di apppoggio consumi
    int diff=data1.daysTo(data2)+1;

    for (size_t i = 0; i < consum_user.size(); i++)
    {
        QDate currentdate(consum_user[i]->get_data().tm_year,consum_user[i]->get_data().tm_mon,consum_user[i]->get_data().tm_mday);

        if(data1<=currentdate && data2>=currentdate){

           avg_month+=consum_user[i]->get_consumption();
        }
    }
    Struttura_dati::deinit_score_ranges(consum_user);
    consum_user.clear();

   return ((avg_month = avg_month / diff)*30);
}
