#include "mainwindow.h"
#include "water_reading.h"
#include "input_file.h"
#include "drag_drop.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    std::map <std::string,std::vector<water_reading*>> Wreading;    //map within id linked to own vector of water readings
    QApplication a(argc, argv);
    drag_drop* w = new drag_drop();
    w->show();
    return a.exec();
}



