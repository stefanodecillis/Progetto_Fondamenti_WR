#include<visualizzaione.h>
#include "ui_visualizzaione.h"
#include <qdebug.h>
#include<qstring.h>
#include<struttura_dati.h>


visualizzaione::visualizzaione(QWidget *parent):
    QWidget(parent),
    ui(new Ui::visualizzaione)
{
    ui->setupUi(this);
    ui->customPlot->hide();
}

void visualizzaione::aggiungi_grafico(){//grafico1- funzionalitàa 1
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
    QVector<double>  regenData;
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12;//numeri colonne
    labels << "Gennaio" << "Febbraio" << "Marzo" << "Aprile" << "Maggio" << "Giugno" << "Luglio" << "Agosto" << "Settembre" << "Ottobre" << "Novembre" << "Dicembre";//nomi per colonne
    //aggiungo dati x e y
    ui->customPlot->xAxis->setTickVector(ticks);//numero colonne
    ui->customPlot->xAxis->setTickVectorLabels(labels);
    ui->customPlot->xAxis->setRange(0, 13);//numero colonne+1

    QCPBars *regen2 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
     ui->customPlot->addPlottable(regen2);
    QString da=ui->textbox1->text();//codice cliente
    std::vector<double> appoggio;//qui ci salvo i valori restituiti dalla funzione Consumo_tot-epr_month

    for(int i=1;i<13;i++){
        regenData<<visualizzaione::Consumo_tot_per_month(i,da.toStdString(),appoggio);
    }
    //ricorda setto coordinate max y .
    auto biggest = std::max_element(std::begin(appoggio), std::end(appoggio));
     auto mino = std::min_element(std::begin(appoggio), std::end(appoggio));
    //trovo media
    double accomu=0;
    for(size_t i=0;i<appoggio.size();i++)accomu+=appoggio.at(i);
    accomu=(accomu/appoggio.size());
    QPen pen;
    pen.setWidth(1.2);
    pen.setColor(QColor(255,131,20));
    regen2->setPen(pen);
    regen2->setBrush(QColor(255,131,0,50));
    qDebug()<<*biggest<<" valore big";//non funge per ora
     qDebug()<<*mino<<" valore small";
     qDebug()<<accomu<<" media";
    ui->customPlot->yAxis->setRange(0,*biggest);//numeri y range
    regen2->setData(ticks, regenData);//inserisce i valori delle colonne
    ui->customPlot->replot();
}




double visualizzaione::Consumo_tot_per_month(int month,std::string stringa,std::vector<double> &app){
    //per ogni mese e codice persona, sommo tutti i consumi
    double tot=0;
    for(size_t t=0;t<Struttura_dati::Wreading.at(stringa).size();t++){
        if(month==Struttura_dati::Wreading.at(stringa)[t]->get_data().tm_mon){
            tot+=Struttura_dati::Wreading.at(stringa)[t]->get_consumption();
            app.push_back(tot);
        }}
    qDebug()<<month<<"->"<<tot;
    return tot;
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
            visualizzaione::aggiungi_grafico();
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(2,false);
        }else if(ui->comboBox1->currentText().toStdString()=="Mensile"){
            ui->tabWidget->setCurrentIndex(1);
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(2,false);
        }else if(ui->comboBox1->currentText().toStdString()=="Giornaliero"){
            ui->tabWidget->setCurrentIndex(2);
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,false);
        }else{
            //non fare nulla, caso default...perchè accetta anche stringa vuota ""
        }
    }//fine if
}
