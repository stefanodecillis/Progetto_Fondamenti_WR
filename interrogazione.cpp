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
            msgBox.setText("errore inserimento dato..perchè la data due<data1");
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
        msgBox.setText("adesso i dati sono validi!");//ricordo di settare il contatore
        msgBox.exec();
    }
//qDebug()<<date;
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
        QMessageBox msgBox;
        msgBox.setText("DATI VALIDI");//ho id e data corretta
        msgBox.exec();


        QDate data1 = this->date1;
        //qDebug()<<data1;
         QDate data2 = this->date2;
         //qDebug()<<data2;

          double totalcons = total_consumption(data1,data2,ui->Find_user->text().toStdString());
ui->setHere_tot->setText(QString::number(totalcons));
        qDebug()<<QString::number(totalcons);
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
   /*
    tm begin;
    tm end;

    begin.tm_year = data1.year();
    begin.tm_mon = data1.month();
    begin.tm_mday = data1.daysInMonth();
    end.tm_year = data2.year();
    end.tm_mon = data2.month();
    end.tm_mday = data2.daysInMonth();
    */

    std::vector<double> values;

     qDebug()<<"grandezza vector"<<QString::number(consum_user.size());
    for (size_t i = 0; i < consum_user.size(); i++)
    {
        //Inserisco i valori compresi tra le due date
        QDate nuovo(consum_user[i]->get_data().tm_year,consum_user[i]->get_data().tm_mon,consum_user[i]->get_data().tm_mday);
     if(data1<=nuovo && data2>=nuovo){
     values.push_back(consum_user[i]->get_consumption());
     }
}

   // double avg_hourly = values[0];
     qDebug()<<"grandezza vector piccolo"<<QString::number(values.size());
    double total_consumption=0;
    for (size_t i = 0; i<values.size(); i++)
    {
        total_consumption += values[i];
        //avg_hourly = avg_hourly/2;
    }


return total_consumption;
}


