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
    water_reading(std::string time,std::string consum);
    water_reading (float consumption,tm data);
    tm get_data();
    float get_consumption(){return consumption;}
    bool compare(water_reading a, int depth);
    bool operator <(water_reading b) {
        return compare(b,0);
    }
    bool operator >(water_reading b)
    {
        return !(compare(b,0));
    }

    std::string printDate();
};


#endif // WATER_READING_H
