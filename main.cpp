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

    drag_drop* w = new drag_drop();
    w->show();



    return a.exec();
    //
}



