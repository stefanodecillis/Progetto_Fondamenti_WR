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
//temp per analisi
    static std::map<std::string, std::vector<double>> map;
    static std::vector<double> avg_for_index;//salvo tutte le medie di tutte le utenze


    //
     static QString FilePath;
     static std::vector<std::string>index;
     static void sort_vect(std::map <std::string, std::vector<water_reading*> > &map, std::string user);
     static std::vector<water_reading*> score_ranges(std::vector<water_reading*> vect_user);
     static bool sort_function(water_reading* a, water_reading* b);
     static void deinit_score_ranges (std::vector<water_reading*> &vect_toDelete);
};

#endif // STRUTTURA_DATI_H
