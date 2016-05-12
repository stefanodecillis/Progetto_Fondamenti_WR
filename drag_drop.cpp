#include "drag_drop.h"
#include "ui_drag_drop.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>
#include <QString>
#include "water_reading.h"
#include <QProgressDialog>
#include "input_file.h"
#include <string>
#include<menu.h>
#include<struttura_dati.h>

#ifdef OS_WINDOWS
#define WIN 8
#else
#define WIN 7   // 7 per UNIX 8 per WINDOWS
#endif



drag_drop::drag_drop(QWidget *parent):
    QWidget(parent),
    ui(new Ui::drag_drop)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    setAutoFillBackground(true);
    setMaximumSize(200,200);
    setMinimumSize(200,200);
    connect(this,SIGNAL(sendstring(QString)),this,SLOT(setValue(QString)));
}
void drag_drop::setValue(QString str){ //stampa quello passato dal sender, qui esplicito un nome della variabile

    Struttura_dati::FilePath =str;//salvo nella classe con membri static

    QProgressDialog progress("Caricamento Dati", "Stop", 0, 0,this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    if(!(input_file::read_file(Struttura_dati::Wreading,Struttura_dati::FilePath.toStdString(),&progress))){
        //non ha finito di caricare..pulisco la mappa..
        Struttura_dati::map.clear();
        Struttura_dati::index.clear();


    }else{
        std::vector<std::string>indici;
        for(auto i: Struttura_dati::Wreading){
            indici.push_back(i.first);
        }
        Struttura_dati::index=indici;
        Menu *p=new Menu;//instanzio visualizzo e chiudo il form corrente
        p->show();
        this->close();
    }
}

void drag_drop::dragEnterEvent(QDragEnterEvent* event){
    event->acceptProposedAction();
}

void drag_drop::dragLeaveEvent(QDragLeaveEvent* event){
    event->accept();
}

void drag_drop::dragMoveEvent(QDragMoveEvent* event){
    event->accept();
}

void drag_drop::dropEvent(QDropEvent* event){
    QList <QUrl> urls;
    QString path = event ->mimeData()->urls().at(0).toString();
    std::string path_str = path.toStdString();
    QString subString=path.mid(WIN,path.size()-WIN);//lavoro la stringa perchè dopo sia valida per la lettura da file
    emit sendstring(subString);//passa il parametro alla funzione del sender, ed avvia il segnale alla classe menu
    event->accept();
}


drag_drop::~drag_drop()
{
    delete ui;
}
