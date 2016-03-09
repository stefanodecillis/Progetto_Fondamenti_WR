#ifndef STRUTTURA_DATI_H
#define STRUTTURA_DATI_H
#include<string>
#include<map>
#include<vector>
#include<qstring.h>
#include<water_reading.h>
class Struttura_dati
{
public:
     static std::map <std::string,std::vector<water_reading*>> Wreading;
     static QString FilePath;
     static std::vector<std::string>index;
     static void sort_vect(std::map <std::string, std::vector<water_reading*> > &map, std::string user);
     static std::vector<water_reading*> score_ranges(std::vector<water_reading*> vect_user);
     static bool sort_function(water_reading* a, water_reading* b);
};

#endif // STRUTTURA_DATI_H
