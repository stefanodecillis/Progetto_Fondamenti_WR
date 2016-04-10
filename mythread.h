//Create a class (ex. myThread) and subclass it to QObject

#include <QObject>
#include <QDebug>
#include <QThread>

class MyThread : public QObject
{
  Q_OBJECT

  public:
      explicit MyThread(QObject *parent = 0);

      //This passes a reference to the thread and will connect signals and slots
      //When the thread is started, DoWork will be emmited.
      void DoSetup(QThread &cThread);

  signals:

  public slots:
      //
      void DoWork();

};
