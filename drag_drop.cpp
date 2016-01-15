#include "drag_drop.h"
#include "ui_drag_drop.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>
#include <QString>


drag_drop::drag_drop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drag_drop)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    setAutoFillBackground(true);
}

void drag_drop::dragEnterEvent(QDragEnterEvent* event){
    QString nome;
    QList <QUrl> urls;
    QList<QUrl>::iterator i;
    QString path = event ->mimeData()->urls().at(0).toString();


    event->accept();

}

void drag_drop::dragLeaveEvent(QDragLeaveEvent* event){
    event->accept();
}

void drag_drop::dragMoveEvent(QDragMoveEvent* event){
    event->accept();
}

void drag_drop::dropEvent(QDropEvent* event){
    event->accept();

}

drag_drop::~drag_drop()
{
    delete ui;
}
