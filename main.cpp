#include<qstring.h>
#include<menu.h>
#include<qmessagebox.h>
#include "water_reading.h"
#include "input_file.h"
#include "drag_drop.h"
#include <QApplication>
#include<qdebug.h>
#include<visualizzaione.h>
#include<struttura_dati.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //instanzio i due oggetti per la connect..NECESSARio
    Menu* t= new Menu();
    drag_drop* w = new drag_drop();
    w->show();
    QObject::connect(w,SIGNAL(sendstring(QString)),t,SLOT(setValue(QString)));
    /*
    //prova_funzionamento_testing

  input_file::read_file(Struttura_dati::Wreading,Struttura_dati::FilePath.toStdString());
// scorre tutti i valori della mappa
std::vector<std::string>indici;
 for(auto i: Struttura_dati::Wreading){
    indici.push_back(i.first);
 }
 Struttura_dati::index=indici;

    visualizzaione* t = new visualizzaione();
    t->show();
    */
    return a.exec();
    //
}



