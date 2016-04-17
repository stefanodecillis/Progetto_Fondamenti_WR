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
#include<qprogressdialog.h>

class input_file : public QObject //classe derivata, qobject
{
    Q_OBJECT
public:
    static bool read_file(std::map<std::string, std::vector<water_reading *> > &reading_map, std::string path, QProgressDialog *loadingwindow);
    static bool fill_in (const std::string &line, std::map<std::string, std::vector<water_reading *> > &reading_map);
   static unsigned long allBytes(std::string path);
};

#endif // INPUT_FILE_H
