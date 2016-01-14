#include "drag_drop.h"
#include "ui_drag_drop.h"
#include <QDragEnterEvent>
#include <QMimeData>

drag_drop::drag_drop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drag_drop)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    setAutoFillBackground(true);
}

void drag_drop::dragEnterEvent(QDragEnterEvent* event){
    event->accept();

}

void drag_drop::dragLeaveEvent(QDragLeaveEvent* event){
    event->accept();
}

void drag_drop::dragMoveEvent(QDragMoveEvent* event){
    event->accept();
}

void drag_drop::dropEvent(QDropEvent* event){
    QList <QUrl> path= event->mimeData()->urls();


}

drag_drop::~drag_drop()
{
    delete ui;
}
