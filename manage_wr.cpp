#include "manage_wr.h"

manage_wr::manage_wr()
{

}

void giveMe_consumVect(cwater_reading* first,cwater_reading* last,std::vector<cwater_reading*> &newVect){
    float temp = 0;
    temp = first->get_consum();
    ++first;
    while (first!=last){
        std::string consumption = std::to_string(first->get_consum() - temp);
        cwater_reading* newWr = new cwater_reading(consumption,consumption);  //copy time !!
       temp = first->get_consum();
       newVect.push_back(newWr);
       ++first;
    }                       // i'm not deleting this instance cause it will be used throughout this program
}

void manage_wr::readthatfile(std::string path, std::map <std::string,std::vector<cwater_reading*>> &mappa)
{

}
