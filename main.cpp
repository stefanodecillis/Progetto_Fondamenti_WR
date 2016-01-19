#include "mainwindow.h"
#include "cwater_reading.h"
#include "input_file.h"
#include "drag_drop.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    std::map <std::string,std::vector<cwater_reading*>> database;    //map within id linked to own vector of water readings
    QApplication a(argc, argv);
    drag_drop* w = new drag_drop(NULL);
    w->show();
    return a.exec();
}


/*
 Ti ho creato due nuove classi al posto di Droppath. QMyMap serve per fare il connect della mappa, mentre in drag and drop :: dropfile c'è un signale che connette invece il path del file.
I due segnali dovrebbero arrivare alla classe "connect_map_path" e tramite connect (puoi vedere tutto nel costruttore di quella classe) dovrebbero arrivare al metodo che sta sotto che, in sostanza,
dovrebbe evocare il metodo di lettura del file. Se non ti è chiaro qualcosa puoi contattarmi tranquillamente :) Anyway se fai start dà degli errori che non sono riuscito a risolvere. Se puoi cerca
di risolvere questi errori che sicuramente sei piu bravo di me in questo campo :D
Pushiamo l'elaborato quando vuoi, anche la sera tardi:)
  */
