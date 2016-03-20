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
private slots:
    void on_Return_clicked();
    void on_calendarWidget_clicked(const QDate &date);


    void on_lineEdit_editingFinished();

private:
    Ui::Interrogazione *ui;
    bool input_codice_cliente=false;
    QDate date1;//ci salvo l'intervallo di date per l'interroazione
    QDate date2;
    int count=0;//variabile che controlla che inserisca soltanto una dupla di dati, per i vaori dell'interrogazione
};

#endif // INTERROGAZIONE_H
