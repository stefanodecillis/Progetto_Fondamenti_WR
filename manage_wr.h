#ifndef MANAGE_WR_H
#define MANAGE_WR_H
#include "cwater_reading.h"
#include <map>
#include <vector>

class manage_wr
{
private:
    manage_wr();
public:
    //given wr concerned, creates new vector with consumptions
    void giveMe_consumVect(std::vector<cwater_reading*> *first,std::vector<cwater_reading*> *last,std::vector<cwater_reading> &newVect);
    void readthatfile(std::string path, std::map <std::string,std::vector<cwater_reading*>> &mappa);
};

#endif // MANAGE_WR_H
