

#include <QObject>
#include <QDebug>
#include <QThread>
#include<qtimer>
#include"QtCore"
#include"input_file.h"
#include"water_reading.h"
#include"struttura_dati.h"
#include"qmutex.h"


class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(const QString &parameter) {
        QString result;
        /* ... here is the expensive or blocking operation ... */
        emit resultReady(result);
    }

signals:
    void resultReady(const QString &result);
};

class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    Controller() {
        Worker *worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::operate, worker, &Worker::doWork);
        connect(worker, &Worker::resultReady, this, &Controller::handleResults);
        workerThread.start();
    }
    ~Controller() {
        workerThread.quit();
        workerThread.wait();
    }
public slots:
    void handleResults(const QString &);
signals:
    void operate(const QString &);
};



























/*
class Worker : public QObject
{
    Q_OBJECT
private slots:
    void onTimeout()
    {
        QMutex mutex;
          mutex.lock();

          mutex.unlock();

        qDebug()<<"Worker:: "<<QThread::currentThreadId();
        //input_file::read_file(Struttura_dati::Wreading,Struttura_dati::FilePath.toStdString());
    }
};

class Thread : public QThread
{
    Q_OBJECT

private:
    void run()
    {
        qDebug()<<"thread n*: "<<currentThreadId();


        Worker worker;
        QTimer timer;
        connect(&timer, SIGNAL(timeout()), &worker, SLOT(onTimeout()));
        timer.start(1000);
this->quit();
        exec();
    }
};*/
