

#include "worker.h"
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include<input_file.h>
#include<struttura_dati.h>
#include<water_reading.h>
#include<visualizzaione.h>



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

    for (auto x: Struttura_dati::Wreading)
    {
        Struttura_dati::map[x.first];
        for (int month = 1; month <= 12; month++)
        {
                std::vector<double>consum_daily = visualizzaione::monthly(month,x.first); //acquisto i valori
                //salvo nella mappa
                //mi salvo la media di questo utente
                double avg = 0;
                for (size_t n = 0; n < consum_daily.size(); n++)
                {
                    Struttura_dati::map.at(x.first).push_back(consum_daily.at(n));
                    Struttura_dati::avg_for_index.push_back(consum_daily.at(n));
                }

                consum_daily.clear();
                consum_daily.shrink_to_fit();         
        }//for tutti i mesi
    }//for id

    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"processo finito"<<thread()->currentThreadId();
    emit finished();
}
