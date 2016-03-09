#include<struttura_dati.h>
#include<string>

QString Struttura_dati::FilePath="";
std::map <std::string,std::vector<water_reading*>> Struttura_dati::Wreading;
std::vector<std::string> Struttura_dati::index;


void Struttura_dati::sort_vect(std::map <std::string, std::vector<water_reading*> > &map, std::string user)
{
    std::sort(map.at(user).begin(), map.at(user).end(),sort_function);
}


std::vector<water_reading*> Struttura_dati::score_ranges(std::vector<water_reading*> vect_user)
{
    std::vector<water_reading*> vect_cons;
    for (size_t it = 0, it2 =1; it2 < vect_user.size(); it++, it2++)
    {
        water_reading* newRec = new water_reading(vect_user[it2]->get_consumption() - vect_user[it]->get_consumption(),vect_user[it2]->get_data());
        vect_cons.push_back(newRec);

    }
    return vect_cons;
}
bool Struttura_dati::sort_function(water_reading* a, water_reading* b)
{
    return *a<*b;
}


