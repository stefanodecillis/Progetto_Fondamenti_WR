#include "interrogazione.h"
#include "ui_interrogazione.h"
#include "menu.h"
#include<qdebug.h>
#include<qmessagebox.h>
#include<struttura_dati.h>

Interrogazione::Interrogazione(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interrogazione)
{
    ui->setupUi(this);
    setMaximumSize(714,505);
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




qDebug()<<date;
}

void Interrogazione::on_lineEdit_editingFinished()
{
    //controlla se l'id specificato esiste o meno
    for(size_t i=0;i<Struttura_dati::index.size();i++){
        QString nuova=QString::fromStdString(Struttura_dati::index.at(i));
        if(ui->lineEdit->text()==nuova){
            input_codice_cliente=true;
            ui->lineEdit->setStyleSheet("QLineEdit{border:2px solid green;}");
            qDebug()<<nuova;
            return ;
        }
    }
    //se non esiste non faccio nemmeno la ricerca..meglio dare messaggio di avviso
    input_codice_cliente=false;
    ui->lineEdit->setStyleSheet("QLineEdit{border:2px solid red;}");
}

void Interrogazione::on_pushButton_2_clicked()
{
    this->count=0;
    ui->data1->setText("");
    ui->data2->setText("");
QDate null1;
QDate null2;
    this->date1=null1;
    this->date2=null2;

}

void Interrogazione::on_pushButton_clicked()
{
    //se il dato input è valido e le date sono valide
    if(this->input_codice_cliente==true&&this->date1.isValid()&&this->date2.isValid()){
        QMessageBox msgBox;
        msgBox.setText("DATI VALIDI");
        msgBox.exec();
    }else{
        QMessageBox msgBox;
        msgBox.setText("DATI NON VALIDI");
        msgBox.exec();

    }


}
