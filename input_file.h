#ifndef INPUT_FILE_H
#define INPUT_FILE_H


#include <string>
#include <map>
#include "water_reading.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <QString>
#include<qwidget.h>
#include<qobject.h>
#include <QObject>



class input_file : public QObject //classe derivata, qobject

{
    Q_OBJECT  //bug osx --> run qmake again

public:
    static bool read_file(std::map<std::string, std::vector<water_reading *> > &reading_map, std::string path);
    static bool fill_in (const std::string &line, std::map<std::string, std::vector<water_reading *> > &reading_map);
    input_file(std::map <std::string,std::vector<water_reading*>> &map);

public slots://metodo che riceve la stringa, specificare nella firma solo il tipo
    void setValue(QString);
};

#endif // INPUT_FILE_H
