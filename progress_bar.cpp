#include "progress_bar.h"
#include "ui_progress_bar.h"
#include <QFutureWatcher>
#include <QProgressBar>

progress_bar::progress_bar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::progress_bar)
{
    ui->setupUi(this);


}


void progress_bar::slot_finished()
{
 //thisprogress_bar.hide();
}

progress_bar::~progress_bar()
{
    delete ui;
}

