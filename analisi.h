#ifndef ANALISI_H
#define ANALISI_H
#include<worker.h>
#include <QMainWindow>

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
    static void devianze_mensili(Ui::Analisi *ui);
    static void devianze_settimanali(Ui::Analisi *ui);
     void devianze_giornaliere(Ui::Analisi *ui);
public slots:
    void on_exit_button_clicked();
    void prova();

private slots:
    void on_button_dati_clicked();

    void on_deviance_button_clicked();

private:
    Ui::Analisi *ui;
    QThread *thread;
    Worker *worker;
};

#endif // ANALISI_H
