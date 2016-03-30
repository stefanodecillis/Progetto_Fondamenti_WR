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

#ifdef OS_WINDOWS
  #define WIN 8
#else
  #define WIN 8
#endif
//#include<struttura_dati.h>


drag_drop::drag_drop(QWidget *parent):
    QWidget(parent),
    ui(new Ui::drag_drop)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    setAutoFillBackground(true);
    setMaximumSize(200,200);
    setMinimumSize(200,200);
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
    //QString subString = QString::fromStdString(path_str);
  QString subString=path.mid(WIN,path.size()-WIN);//lavoro la stinga perchè dopo sia valida per la lettura da file
  emit sendstring(subString);//passa il parametro alla funzione del sender, ed avvia il segnale alla classe menu
    Menu *p=new Menu;//instanzio visualizzo e chiudo il fsorm corrente
    p->show();
    this->close();
    event->accept();
}


drag_drop::~drag_drop()
{
    delete ui;
}
