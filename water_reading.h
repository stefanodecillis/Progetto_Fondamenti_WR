#ifndef WATER_READING_H
#define WATER_READING_H

#include <string>
#include <time.h>

class water_reading
{
public:
    water_reading(std::string newdate, std::string newconsumption);
    bool get_valid() {return valid;}
    double get_consumption() {return consumption;}
    tm get_date()  {return date;}
private:
    tm date;
    double consumption;
    bool valid;
};

#endif // WATER_READING_H
