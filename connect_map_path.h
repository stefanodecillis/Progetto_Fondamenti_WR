#ifndef CONNECT_MAP_PATH_H
#define CONNECT_MAP_PATH_H
#include "input_file.h"
#include "drag_drop.h"
#include "qmymap.h"
#include "cwater_reading.h"


class connect_map_path
{
public:
    connect_map_path(std::map<std::__1::string, std::vector<cwater_reading *> > &map);
    void open_readthisfile(std::string* path,std::map<std::string,std::vector<cwater_reading*> > *map);
signals:
    void emit_map(std::map<std::string,std::vector<cwater_reading*> > &map);
};

#endif // CONNECT_MAP_PATH_H
