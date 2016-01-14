#ifndef INPUT_FILE_H
#define INPUT_FILE_H


#include <string>
#include <map>
#include "cwater_reading.h"
#include <iostream>
#include <vector>
#include <fstream>

class input_file{
private:
    input_file();
public:
    static bool read_file(std::map<std::string,std::vector<cwater_reading*>> &reading_map);
    static bool fill_in (const std::string &line, std::map<std::string,std::vector<cwater_reading*>> &reading_map);
};

#endif // INPUT_FILE_H
