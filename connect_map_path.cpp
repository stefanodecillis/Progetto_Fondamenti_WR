#include "connect_map_path.h"
#include "qmymap.h"
#include "drag_drop.h"

connect_map_path::connect_map_path(std::map<std::string, std::vector<cwater_reading*>> &map)
{
    QMyMap* signalMapper = new QMyMap(NULL);
    signalMapper->setMapping(ui->dragAndDrop, map);
    emit emit_map(map);
    connect(ui->dragAndDrop, SIGNAL(sendstring(const std::string)), this, SLOT(open_readthisfile(std::string* path,std::map<std::string,std::vector<cwater_reading*> > &map)));
    connect(signalMapper, SIGNAL(emit_map(std::map<std::string,std::vector<cwater_reading*> > &map)), this, SLOT(open_readthisfile(std::string* path,std::map<std::string,std::vector<cwater_reading*> > &map)));
}



void open_readthisfile(std::string &path,std::map<std::string,std::vector<cwater_reading*> > &map)
 {
 input_file::read_file(map,path);
 }
