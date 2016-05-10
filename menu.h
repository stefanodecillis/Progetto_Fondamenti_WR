#ifndef MENU_H
#define MENU_H
#include <QDialog>
#include<water_reading.h>
#include<worker.h>


namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
private slots:
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();

private:
    Ui::Menu *ui;
    QThread *thread;
    Worker *worker;
};

#endif // MENU_H
