#ifndef INTERROGAZIONE_H
#define INTERROGAZIONE_H

#include <QMainWindow>
#include<QDate>


namespace Ui {
class Interrogazione;
}

class Interrogazione : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interrogazione(QWidget *parent = 0);
    ~Interrogazione();
    static double total_consumption(QDate data1, QDate data2, std::string user);
    static double avg_hourly (QDate data1, QDate data2, std::string user);
    static double avg_daily (QDate data1, QDate data2, std::string user);
private slots:
    void on_Return_clicked();
    void on_calendarWidget_clicked(const QDate &date);


    void on_Find_user_editingFinished();

    void on_Reset_clicked();

    void on_Find_clicked();

private:
    Ui::Interrogazione *ui;
    bool input_codice_cliente=false;
    QDate date1;//ci salvo l'intervallo di date per l'interroazione
    QDate date2;
    int count=0;//variabile che controlla che inserisca soltanto una dupla di dati, per i vaori dell'interrogazione
};

#endif // INTERROGAZIONE_H
