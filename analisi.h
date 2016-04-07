#ifndef ANALISI_H
#define ANALISI_H

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
public slots:
    void on_exit_button_clicked();

private:
    Ui::Analisi *ui;
};

#endif // ANALISI_H
