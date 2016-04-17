

#include "worker.h"
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include<input_file.h>
#include<struttura_dati.h>
#include<water_reading.h>
Worker::Worker(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request di inizio lavoro "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void Worker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"richiesta abort "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

void Worker::doWork()
{
    qDebug()<<"processo iniziato "<<thread()->currentThreadId();
   // input_file::read_file(Struttura_dati::Wreading,Struttura_dati::FilePath.toStdString());
    std::vector<std::string>indici;
     for(auto i: Struttura_dati::Wreading){
        indici.push_back(i.first);
     }
     Struttura_dati::index=indici;
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"processo finito"<<thread()->currentThreadId();
    emit finished();
}
