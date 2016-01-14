#include "mainwindow.h"
#include "cwater_reading.h"
#include "input_file.h"
#include "drag_drop.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    std::map <std::string,std::vector<cwater_reading*>> database;    //map within id linked to own vector of water readings
    input_file::read_file(database);
    QApplication a(argc, argv);
    drag_drop w;
    w.show();

    return a.exec();
}
