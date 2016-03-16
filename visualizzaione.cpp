#include<visualizzaione.h>
#include "ui_visualizzaione.h"
#include <qdebug.h>
#include<qstring.h>
#include<struttura_dati.h>
#include <iostream>


visualizzaione::visualizzaione(QWidget *parent):
    QWidget(parent),
    ui(new Ui::visualizzaione)
{
    ui->setupUi(this);
ui->label_7->setVisible(false);
ui->comboBox->setVisible(false);

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
    pen.setWidth(1.2);
    pen.setColor(QColor(255,131,20));
    regen2->setPen(pen);
    regen2->setBrush(QColor(255,131,0,50));
    qDebug()<<*biggest<<" valore big";
     qDebug()<<mino<<" valore small";
     ui->lineEdit_3->setText(QString::number(mino));
     qDebug()<<avg<<" media";
     qDebug()<<consum_tot(consum_vector)<<" totale";
     //setta valori media,max,min
     ui->lineEdit_4->setText(QString::number(*biggest));
     ui->lineEdit->setText(QString::number(consum_tot(consum_vector)));
     ui->lineEdit_2->setText(QString::number(avg));
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

    ui->customPlot->xAxis->setRange(0, consum_vector.size()+1);//numero colonne+1

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
    double avg= consum_media(consum_vector);
   //colori plot
    QPen pen;
    pen.setWidth(1.2);
    pen.setColor(QColor(255,131,20));
    regen2->setPen(pen);
    regen2->setBrush(QColor(255,190,0,50));
    qDebug()<<*biggest<<" valore big";
     qDebug()<<mino<<" valore small";
     ui->lineEdit_3->setText(QString::number(mino));
     qDebug()<<avg<<" media";
     qDebug()<<consum_tot(consum_vector)<<" totale";
     //setta valori media,max,min
     ui->lineEdit_4->setText(QString::number(*biggest));
     ui->lineEdit->setText(QString::number(consum_tot(consum_vector)));
     ui->lineEdit_2->setText(QString::number(avg));
    ui->customPlot_2->yAxis->setRange(0,*biggest+2);//numeri y range
    regen2->setData(ticks, regenData);//inserisce i valori delle colonne
    ui->customPlot_2->replot();
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
            ui->customPlot_2->close();
            QString user = ui->textbox1->text();
            std::vector<double> values = Consumo_tot_per_month(user.toStdString());
            visualizzaione::aggiungi_grafico(values);
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(2,false);

        }else if(ui->comboBox1->currentText().toStdString()=="Mensile"){
            ui->tabWidget->setCurrentIndex(1);
            ui->customPlot_2->show();
            ui->customPlot->close();
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(2,false);
            std::vector<double> values;


            if(ui->comboBox->currentIndex()==0){//primo caso
                 values = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};//monthly(ui->comboBox1->currentIndex(), ui->textbox1->text().toStdString(), 0);
            }else{//secondo caso
            values = {1,2,3,4,5};//monthly(ui->comboBox1->currentIndex(), ui->textbox1->text().toStdString(), 1);
            }
            visualizzaione::aggiungi_grafico_2(values);

        }else if(ui->comboBox1->currentText().toStdString()=="Giornaliero"){
            ui->tabWidget->setCurrentIndex(2);
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,false);



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

std::vector<double> visualizzaione::monthly(int month, std::string user, int chosen)
{
    Struttura_dati::sort_vect(Struttura_dati::Wreading,user);

   if (chosen == 0)
    {
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
   else if (chosen == 1)
   {
       double tot=0;
       std::vector<double> values;
       std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));
       for (size_t i = 0; i < consum_user.size();i++)
       {
           if (consum_user[i]->get_data().tm_mon == month)
           {
              QDate date(2015,month,consum_user[i]->get_data().tm_mday);
              if (date.dayOfWeek() == 7)
              {
                  tot += consum_user[i]->get_consumption();
                  values.push_back(tot);
                  tot = 0;
              }
              else{
               tot += consum_user[i]->get_consumption();
              }
           }
       }
       values.push_back(tot);
       return values;
   }
}

std::vector<double> visualizzaione::daily (int month, int day, std::string user)
{
    double tot=0;
    std::vector<double> values;
    std::vector<water_reading*> consum_user = Struttura_dati::score_ranges(Struttura_dati::Wreading.at(user));
    for (int hh = 1; hh <= 24; hh++)
    {
        tot = 0;
        for (size_t i = 0; i < consum_user.size(); i++)
        {
            if (consum_user[i]->get_data().tm_mon == month && consum_user[i]->get_data().tm_mday == day && consum_user[i]->get_data().tm_hour == hh)
            {
                tot += consum_user[i]->get_consumption();
            }
        }
        values.push_back(tot);
    }
}



void visualizzaione::on_comboBox1_currentIndexChanged(int index)//evento combobox per mensile-> index=1
{
    if(index==1){//sono a mensile..quindi faccio apparire forms per input

        ui->label_7->setVisible(true);
        ui->comboBox->setVisible(true);
        ui->label_8->setVisible(true);
        ui->comboBox_2->setVisible(true);

    }else{//faccio sparire i form per il mese

        ui->label_7->setVisible(false);
        ui->comboBox->setVisible(false);
        ui->label_8->setVisible(false);
        ui->comboBox_2->setVisible(false);
    }

}
