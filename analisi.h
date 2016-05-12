#ifndef ANALISI_H
#define ANALISI_H
#include<worker.h>
#include <QMainWindow>
#include<qtimer.h>

namespace Ui {
class Analisi;
}

class Analisi : public QMainWindow
{
    Q_OBJECT

public:
    explicit Analisi(QWidget *parent = 0);
    ~Analisi();
     static std::vector<QDate> get_threshold(std::string user, double threshold);
     void devianze_mensili(Ui::Analisi *ui);
     void devianze_settimanali(Ui::Analisi *ui);
     void devianze_giornaliere(Ui::Analisi *ui);
     void IniziaTimer();
public slots:
    void on_exit_button_clicked();
    void dev_giornaliere();
    void onTimeOut();

private slots:
    void on_button_dati_clicked();

    void on_deviance_button_clicked();

private:
    bool isTerminated=false;
    Ui::Analisi *ui;
    QThread *thread;
    Worker *worker;
    QTimer *timer;
    size_t counter;
};

#endif // ANALISI_H
