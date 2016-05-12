#ifndef WATER_READING_H
#define WATER_READING_H

#include <time.h>
#include <string>

class water_reading
{
private:
    tm data;
    float consumption;
public:
    water_reading(std::string time,std::string consum); //costruttori
    water_reading (float consumption,tm data); //costruttori
    tm get_data();
    float get_consumption(){return consumption;}
    bool compare(water_reading a, int depth);
    static bool compare_tm(tm data1,tm data2,int depth);
    bool operator <(water_reading b) {
        return compare(b,0);
    }
    bool operator >(water_reading b)
    {
        return !(compare(b,0));
    }

};


#endif // WATER_READING_H
