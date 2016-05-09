

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
            int day_count = 0;
            switch(month)
            {
            case 1 : case 3 : case 5 :  case 7 : case 8 : case 10 : case 12:
                day_count = 31;
                break;
            case 2:
                day_count = 28;
                break;
            case 4: case 6 : case 9 : case 11 :
                day_count = 30;
                break;
            default:
                day_count = 30;
            }

            for (int day = 1; day <= day_count; day++)
            {
                std::vector<double>consum_daily = visualizzaione::daily(month,day,x.first); //acquisto i valori
                //salvo nella mappa
                //mi salvo la media di questo utente
                double avg = 0;
                for (size_t n = 0; n < consum_daily.size(); n++)
                {
                   Struttura_dati::map.at(x.first).push_back(consum_daily.at(n));
                    avg += consum_daily.at(n);
                }
                avg = avg / consum_daily.size();
                Struttura_dati::avg_for_index.push_back(avg);
                consum_daily.clear();
                consum_daily.shrink_to_fit();
               //std::vector<double>().swap(consum_daily);
            }
        }//for tutti i mesi
    }//for id

    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"processo finito"<<thread()->currentThreadId();
    emit finished();
}
