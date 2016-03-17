#ifndef VISUALIZZAIONE_H
#define VISUALIZZAIONE_H
#include <QWidget>
#include<water_reading.h>
#include <vector>


namespace Ui {
class visualizzaione;
}

class visualizzaione : public QWidget
{
    Q_OBJECT

public:
    explicit visualizzaione(QWidget *parent = 0);
    static std::vector<double> Consumo_tot_per_month( std::string user);
    static double consum_media (std::vector<double>user);
    static double consum_min (std::vector<double> user);
    static double consum_tot (std::vector<double> user);
    static std::vector<double> monthly(int month, std::string user, int chosen);
    static std::vector<double> daily (int month, int day, std::string user);
private slots:
    void on_textbox1_editingFinished();
    void aggiungi_grafico(std::vector<double> const consum_vector);
    void aggiungi_grafico_2(std::vector<double> const consum_vector);
    void aggiungi_grafico_3(std::vector<double> const consum_vector);
    void on_button1_clicked();
    void on_comboBox1_currentIndexChanged(int index);

private:
    Ui::visualizzaione *ui;
    bool input_codice_cliente=false;

};

#endif // VISUALIZZAIONE_H
