

#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = 0);

    void requestWork();

    void abort();

private:

    bool _abort;

    bool _working;

    QMutex mutex;

signals:

    void workRequested();
    void finished();

public slots:
    void doWork();
};

#endif // WORKER_H
