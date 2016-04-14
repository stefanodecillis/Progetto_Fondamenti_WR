#include<visualizzaione.h>
#include "ui_visualizzaione.h"
#include <qdebug.h>
#include<qstring.h>
#include<struttura_dati.h>
#include <iostream>
#include <menu.h>


visualizzaione::visualizzaione(QWidget *parent):
    QWidget(parent),
    ui(new Ui::visualizzaione)
{
    ui->setupUi(this);
ui->label_7->setVisible(false);
ui->comboBox->setVisible(false);
ui ->days->setVisible(false);
ui->giorno->setVisible(false);

ui->label_8->setVisible(false);
ui->comboBox_2->setVisible(false);
ui->customPlot->hide();

}

void visualizzaione::aggiungi_grafico(std::vector<double> const consum_vector){//grafico1
    ui->customPlot->clearPlottables();//pulisco grafico corrente
    // prepare x axis:
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setTickLength(0, 4);//lunghezza righetta verticale-non necessaria
    ui->customPlot->xAxis->grid()->setVisible(true);
    // prepare y axis:
    //N.B il numero y lo setto dopo con il
    ui->customPlot->yAxis->setPadding(3); // spazio la
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
     // Add data:
    QVector<double>regenData;
    QVector<double> ticks;
    QVector<QString> labels;
    //switch per l'input dei dati

    switch(consum_vector.size()){
    case 12://mese
        ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12;//numeri colonne
        labels << "Gennaio" << "Febbraio" << "Marzo" << "Aprile" << "Maggio" << "Giugno" << "Luglio" << "Agosto" << "Settembre" << "Ottobre" << "Novembre" << "Dicembre";//nomi per colonne
        break;
    case 24:
        ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19 << 20 << 21 << 22 <<  23<< 24  ;//numeri colonne
        for (int i = 1; i <=24 ; i++)
        {
            labels << QString::number(i);//nomi per colonne
        }

        break;

    default:
        for(size_t i=1;i<=consum_vector.size();i++){
           ticks<< i;
           labels<< QString::number(i);
        }
        break;
    }


    //aggiungo dati x e y
    ui->customPlot->xAxis->setTickVector(ticks);//numero colonne
    ui->customPlot->xAxis->setTickVectorLabels(labels);

    ui->customPlot->xAxis->setRange(0, consum_vector.size()+1);//numero colonne+1

    QCPBars *regen2 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
     ui->customPlot->addPlottable(regen2);

    for(size_t i=0;i<consum_vector.size();i++){
    regenData<<consum_vector.at(i);
    }

    //ricorda setto coordinate max y .
    auto biggest = std::max_element(std::begin(consum_vector), std::end(consum_vector));
     double mino = *(std::min_element(std::begin(consum_vector), std::end(consum_vector)));
     std::cout << mino << std::endl;
    //trovo media
    double avg= consum_media(consum_vector);
   //colori plot
    QPen pen;
    QString mc = "m³";
    pen.setWidth(1.2);
    pen.setColor(QColor(255,131,20));
    regen2->setPen(pen);
    regen2->setBrush(QColor(255,131,0,50));
    qDebug()<<*biggest<<" valore big";
     qDebug()<<mino<<" valore small";
     ui->lineEdit_3->setText(QString::number(mino)+mc);
     qDebug()<<avg<<" media";
     qDebug()<<consum_tot(consum_vector)<<" totale";
     //setta valori media,max,min
     ui->lineEdit_4->setText(QString::number(*biggest) + mc);
     ui->lineEdit->setText(QString::number(consum_tot(consum_vector))+mc);
     ui->lineEdit_2->setText(QString::number(avg)+mc);
    ui->customPlot->yAxis->setRange(0,*biggest+2);//numeri y range
    regen2->setData(ticks, regenData);//inserisce i valori delle colonne
    ui->customPlot->replot();
}

//Grafico 2 --- Mensile

void visualizzaione::aggiungi_grafico_2(std::vector<double> const consum_vector){//grafico1
    ui->customPlot_2->clearPlottables();//pulisco grafico corrente
    // prepare x axis:
    ui->customPlot_2->xAxis->setAutoTicks(false);
    ui->customPlot_2->xAxis->setAutoTickLabels(false);
    ui->customPlot_2->xAxis->setTickLabelRotation(60);
    ui->customPlot_2->xAxis->setTickLength(0, 4);//lunghezza righetta verticale-non necessaria
    ui->customPlot_2->xAxis->grid()->setVisible(true);
    // prepare y axis:
    //N.B il numero y lo setto dopo con il
    ui->customPlot_2->yAxis->setPadding(3); // spazio la
    ui->customPlot_2->yAxis->grid()->setSubGridVisible(true);
    // Add data:
    QVector<double>regenData;
    QVector<double> ticks;
    QVector<QString> labels;
    //switch per l'input dei dati

    for(size_t i=1;i<=consum_vector.size();i++){
        ticks<< i;
        labels<< QString::number(i);
}

    //aggiungo dati x e y
    ui->customPlot_2->xAxis->setTickVector(ticks);//numero colonne
    ui->customPlot_2->xAxis->setTickVectorLabels(labels);

    ui->customPlot_2->xAxis->setRange(0, consum_vector.size()+1);//numero colonne+1

    QCPBars *regen2 = new QCPBars(ui->customPlot_2->xAxis, ui->customPlot_2->yAxis);
     ui->customPlot_2->addPlottable(regen2);

    for(size_t i=0;i<consum_vector.size();i++){
    regenData<<consum_vector.at(i);
    }

    //ricorda setto coordinate max y .
    auto biggest = std::max_element(std::begin(consum_vector), std::end(consum_vector));
     double mino = *(std::min_element(std::begin(consum_vector), std::end(consum_vector)));
     std::cout << mino << std::endl;
    //trovo media
     double tot = consum_max(ui->textbox1->text().toStdString());
    double avg= consum_media(consum_vector);
    double high = (*biggest /10);
   //colori plot
    QString mc = "m³";
    QPen pen;
    pen.setWidth(1.2);
    pen.setColor(QColor(255,131,20));
    regen2->setPen(pen);
    regen2->setBrush(QColor(255,190,0,50));
    qDebug()<<*biggest<<" valore big";
     qDebug()<<mino<<" valore small";
     ui->lineEdit_3->setText(QString::number(mino)+ mc);
     qDebug()<<avg<<" media";
     qDebug()<<consum_tot(consum_vector)<<" totale";
     //setta valori media,max,min
     ui->lineEdit_4->setText(QString::number(*biggest)+ mc);
     ui->lineEdit->setText(QString::number(tot)+ mc);
     ui->lineEdit_2->setText(QString::number(avg)+ mc);
    ui->customPlot_2->yAxis->setRange(0,*biggest+ high);//numeri y range
    regen2->setData(ticks, regenData);//inserisce i valori delle colonne
    ui->customPlot_2->replot();
}


void visualizzaione::aggiungi_grafico_3(std::vector<double> const consum_vector){//grafico1
    ui->customPlot_3->clearPlottables();//pulisco grafico corrente
    // prepare x axis:
    ui->customPlot_3->xAxis->setAutoTicks(false);
    ui->customPlot_3->xAxis->setAutoTickLabels(false);
    ui->customPlot_3->xAxis->setTickLabelRotation(60);
    ui->customPlot_3->xAxis->setTickLength(0, 4);//lunghezza righetta verticale-non necessaria
    ui->customPlot_3->xAxis->grid()->setVisible(true);
    // prepare y axis:
    //N.B il numero y lo setto dopo con il
    ui->customPlot_3->yAxis->setPadding(3); // spazio la
    ui->customPlot_3->yAxis->grid()->setSubGridVisible(true);
    // Add data:
    QVector<double>regenData;
    QVector<double> ticks;
    QVector<QString> labels;
    //switch per l'input dei dati

    for(size_t i=1;i<=consum_vector.size();i++){
        ticks<< i;
        labels<< QString::number(i);
}

    //aggiungo dati x e y
    ui->customPlot_3->xAxis->setTickVector(ticks);//numero colonne
    ui->customPlot_3->xAxis->setTickVectorLabels(labels);

    ui->customPlot_3->xAxis->setRange(0, consum_vector.size()+1);//numero colonne+1

    QCPBars *regen2 = new QCPBars(ui->customPlot_3->xAxis, ui->customPlot_3->yAxis);
     ui->customPlot_3->addPlottable(regen2);

    for(size_t i=0;i<consum_vector.size();i++){
    regenData<<consum_vector.at(i);
    }

    //ricorda setto coordinate max y .
    auto biggest = std::max_element(std::begin(consum_vector), std::end(consum_vector));
     double mino = *(std::min_element(std::begin(consum_vector), std::end(consum_vector)));
     std::cout << mino << std::endl;
    //trovo media
    double avg= consum_media(consum_vector);
   //colori plot
    QString mc = "m³";
    QPen pen;
    pen.setWidth(1.2);
    pen.setColor(QColor(255,131,20));
    regen2->setPen(pen);
    regen2->setBrush(QColor(255,190,0,50));
    qDebug()<<*biggest<<" valore big";
     qDebug()<<mino<<" valore small";
     ui->lineEdit_3->setText(QString::number(mino)+ mc);
     qDebug()<<avg<<" media";
     qDebug()<<consum_tot(consum_vector)<<" totale";
     //setta valori media,max,min
     ui->lineEdit_4->setText(QString::number(*biggest)+ mc);
     ui->lineEdit->setText(QString::number(consum_max(ui->textbox1->text().toStdString()))+ mc);
     ui->lineEdit_2->setText(QString::number(avg)+ mc);
    ui->customPlot_3->yAxis->setRange(0,*biggest);//numeri y range
    regen2->setData(ticks, regenData);//inserisce i valori delle colonne
    ui->customPlot_3->replot();
}

std::vector<double> visualizzaione::Consumo_tot_per_month(std::string user){
    //per ogni mese e codice persona, sommo tutti i consumi
    double tot=0;
    std::vector<double> values;
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);
    std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));
    for (int month = 1; month<= 12;month++)
    {
        tot = 0;
        for (size_t i = 0; i < consum_user.size(); i++)
        {
            if (consum_user[i]->get_data().tm_mon == month)
            {
                tot += consum_user[i]->get_consumption();
            }
        }
        values.push_back(tot);
    }
    if (values.size() == 0)
    {
        values.push_back(0);values.push_back(0);values.push_back(0);values.push_back(0); //Se non ho valori, l'utente non ha consumato nulla in questo mese
    }

   return values;
}



void visualizzaione::on_textbox1_editingFinished()//validazione input dell'utente
{
    //controlla se l'id specificato esiste o meno
    for(size_t i=0;i<Struttura_dati::index.size();i++){
        QString nuova=QString::fromStdString(Struttura_dati::index.at(i));
        if(ui->textbox1->text()==nuova){
            input_codice_cliente=true;
            ui->textbox1->setStyleSheet("QLineEdit{border:2px solid green;}");
            qDebug()<<nuova;
            return ;
        }
    }
    //se non esiste non faccio nemmeno la ricerca..meglio dare messaggio di avviso
    input_codice_cliente=false;
    ui->textbox1->setStyleSheet("QLineEdit{border:2px solid red;}");
}

void visualizzaione::on_button1_clicked()
{

    if(input_codice_cliente){//dati validi //ps. nota che c'è il valore di stringa vuota
        if(ui->comboBox1->currentText().toStdString()=="Annuale"){
            ui->tabWidget->setCurrentIndex(0);
            ui->customPlot->show();
            ui->customPlot_2->hide();
            ui->customPlot_3->hide();
            QString user = ui->textbox1->text();
            std::vector<double> values = Consumo_tot_per_month(user.toStdString());
            visualizzaione::aggiungi_grafico(values);
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(2,false);


        }else if(ui->comboBox1->currentText().toStdString()=="Mensile"){
            ui->tabWidget->setCurrentIndex(1);
            ui->customPlot_2->show();
            ui->customPlot->hide();
            ui->customPlot_3->hide();
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(2,false);
            std::vector<double> values;
            if(ui->comboBox->currentIndex()==0){//primo caso
                 values = monthly(ui->comboBox_2->currentIndex(), ui->textbox1->text().toStdString());
            }else{//secondo caso
            values = weekly( ui->textbox1->text().toStdString(),ui->comboBox_2->currentIndex()+1);
            }
            visualizzaione::aggiungi_grafico_2(values);


        }else if(ui->comboBox1->currentText().toStdString()=="Giornaliero"){
            ui->tabWidget->setCurrentIndex(2);
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,false);
            ui->customPlot->hide();
            ui->customPlot_2->hide();
            ui->customPlot_3->show();
            QString user = ui->textbox1->text();
           std::vector<double> values;
           values = daily(ui->comboBox_2->currentIndex()+1,ui->days->currentIndex()+1,user.toStdString());
           visualizzaione::aggiungi_grafico_3(values);

        }else{
            //non fare nulla, caso default...perchè accetta anche stringa vuota ""
        }
    }//fine if
}
double visualizzaione::consum_media (std::vector<double> user)
{
    double tot = 0;
    for (size_t i = 0; i<user.size();i++)
    {
        tot += user[i];
    }
    if (user.size() == 0)
        return tot = 0;

    tot = tot / user.size();
    return  tot;
}

double visualizzaione::consum_min (std::vector<double> user)
{
    double min = user.at(0);
    for (size_t i = 0; i < user.size(); i++)
    {
     if (user.at(i) < min) {
         min = user.at(i);
     }
    }
    return min;
}

double visualizzaione::consum_tot(std::vector<double> user){
    double tot=0;
    for (size_t i = 0; i < user.size(); i++)tot+=user.at(i);
   return tot;
}

std::vector<double> visualizzaione::monthly(int month, std::string user)
{
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);
    month++;
        int day = 0;
        switch(month)
        {
        case 1 : case 3 : case 5 :  case 7 : case 8 : case 10 : case 12:
            day = 31;
            break;
        case 2:
            day = 28;
            break;
        case 4: case 6 : case 9 : case 11 :
            day = 30;
            break;
        default:
            day = 30;
        }
        double tot=0;
        std::vector<double> values;
        std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));
        for (int i = 1; i <= day; i++)
        {
            tot = 0;
            for (size_t j = 0; j < consum_user.size(); j++)
            {
                if (consum_user[j]->get_data().tm_mon == month && consum_user[j]->get_data().tm_mday == i)
                {
                    tot+= consum_user[j]->get_consumption();
                }
            }
          values.push_back(tot);
        }
        return values;

}

std::vector<double> visualizzaione::daily (int month, int day, std::string user)
{
    double tot=0;
    std::vector<double> values;
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);
    std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));
    for (int hh = 0; hh <= 23; hh++)
    {

        for (size_t i = 0; i < consum_user.size(); i++)
        {
            if (consum_user[i]->get_data().tm_mon == month && consum_user[i]->get_data().tm_mday == day && consum_user[i]->get_data().tm_hour == hh)
            {
              tot += consum_user[i]->get_consumption();
            }
        }

       values.push_back(tot);
       tot = 0;
    }
    return values;
}



void visualizzaione::on_comboBox1_currentIndexChanged(int index)//evento combobox
{
    if(index==0){//sono a mensile..quindi faccio apparire forms per input
        ui->label_7->setVisible(false);
        ui->comboBox->setVisible(false);
        ui->label_8->setVisible(false);
        ui->comboBox_2->setVisible(false);
        ui->giorno->setVisible(false);
        ui->days->setVisible(false);
        ui->giorno->setVisible(false);
    }else if(index==1){//faccio sparire i form per il mese
        ui->days->setVisible(false);
        ui->label_7->setVisible(true);
        ui->comboBox->setVisible(true);
        ui->label_8->setVisible(true);
        ui->comboBox_2->setVisible(true);
        ui->giorno->setVisible(false);
    }else if(index==2){
        ui->days->setVisible(true);
        ui->giorno->setVisible(true);
        ui->label_7->setVisible(false);
        ui->comboBox->setVisible(false);
        ui->label_8->setVisible(true);
        ui->comboBox_2->setVisible(true);
    }
}

void visualizzaione::on_Return_clicked()
{
    Menu* t = new Menu();
    t->show();
    this->close();
}

void visualizzaione::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    if(ui->comboBox1->currentText()=="Giornaliero"){//validazione giornaliero
        if(arg1=="Aprile" || arg1=="Giugno" || arg1=="Settembre" || arg1=="Novembre" ){//30
            ui->days->clear();
            QStringList list=(QStringList()<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20"<<"21"<<"22"<<"23"<<"24"<<"25"<<"26"<<"27"<<"28"<<"29"<<"30");
            ui->days->addItems(list);
        }else if(arg1=="Febbraio"){//28
            ui->days->clear();
            QStringList list=(QStringList()<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20"<<"21"<<"22"<<"23"<<"24"<<"25"<<"26"<<"27"<<"28");
            ui->days->addItems(list);
        }else{//31
            ui->days->clear();
            QStringList list=(QStringList()<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20"<<"21"<<"22"<<"23"<<"24"<<"25"<<"26"<<"27"<<"28"<<"29"<<"30"<<"31");
            ui->days->addItems(list);
        }}
}

std::vector<double> visualizzaione::weekly (const std::string user, int month)
{
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);
    std::vector<water_reading*> vect_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));
    std::vector <double> values;
    double consum = 0;
    for (size_t i = 0; i < vect_user.size(); i++)
    {

        if (vect_user[i]->get_data().tm_mon == month)
        {
            consum += vect_user[i]->get_consumption();
             QDate date(2015,month,vect_user[i]->get_data().tm_mday);
             if (i != vect_user.size()-1)  //controllo se dopo ho un altra lettura (unico metodo per verificare trovato)
             {
                 QDate date2(2015,month,vect_user[i+1]->get_data().tm_mday);
                 if (date.dayOfWeek() == 7 && date2.dayOfWeek() != 7)
                 {
                     values.push_back(consum);
                     consum = 0;
                 }
             }
        }
    }
    if(consum != 0)
    {
         values.push_back(consum);
    }
    if (values.size() == 0)
    {
        values.push_back(0);values.push_back(0);values.push_back(0);values.push_back(0); //Se non ho valori, l'utente non ha consumato nulla in questo mese
    }
    return values;
}

double visualizzaione::consum_max (const std::string user)
{
    double tot=0;
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);
    std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));
  for (size_t i = 0; i < consum_user.size(); i++)
  {
      tot += consum_user[i]->get_consumption();
  }
  return tot;

}
