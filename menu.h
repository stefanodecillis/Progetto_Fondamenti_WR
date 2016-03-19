#ifndef MENU_H
#define MENU_H
#include <QDialog>
#include<water_reading.h>


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
public slots://metodo che riceve la stringa, specificare nella firma solo il tipo
    void setValue(QString);
private:
    Ui::Menu *ui;
};

#endif // MENU_H
