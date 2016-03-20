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
    msgBox.setText("adesso i dati sono validi");//ricordo di settare il contatore
    msgBox.exec();
}




qDebug()<<date;
}
