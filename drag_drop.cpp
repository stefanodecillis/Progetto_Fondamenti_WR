#include "drag_drop.h"
#include "ui_drag_drop.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>
#include <QString>
#include <qdebug.h>
#include "progress_bar.h"
#include "drag_drop.h"
#include "cwater_reading.h"
#include <QProgressDialog>
#include "input_file.h"
#include <string>
#include <map>


drag_drop::drag_drop(QWidget *parent, std::map<std::string, std::vector<cwater_reading *> > &map) :
    QWidget(parent),
    ui(new Ui::drag_drop)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    setAutoFillBackground(true);
    setMaximumSize(200,200);
    setMinimumSize(200,200);
    //reading readhere(map,NULL);
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

void drag_drop::dropEvent(QDropEvent* event,std::map<std::string, std::vector<cwater_reading *> > &map){
    QList <QUrl> urls;
    QString path = event ->mimeData()->urls().at(0).toString();
    std::string path_str = path.toStdString();
    event->accept();
    input_file::read_file(map,path_str);
    progress_bar* dash = new progress_bar();
    dash->show();
}

drag_drop::~drag_drop()
{
    delete ui;
}
