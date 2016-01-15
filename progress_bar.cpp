#include "progress_bar.h"
#include "ui_progress_bar.h"

progress_bar::progress_bar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::progress_bar)
{
    ui->setupUi(this);
}

progress_bar::~progress_bar()
{
    delete ui;
}
