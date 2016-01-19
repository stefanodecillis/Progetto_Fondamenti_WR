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
#include "qmymap.h"


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
    event->accept();
    emit sendstring(path_str);
    //fare connect
}


drag_drop::~drag_drop()
{
    delete ui;
}
