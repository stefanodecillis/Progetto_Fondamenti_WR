#ifndef CWATER_READING_H
#define CWATER_READING_H

#include <string>
#include <time.h>

class cwater_reading
{
    //prototype of readings for ID
    private :
        tm date;     //QDateTime from Qt framework
        float consum;
        bool findError = true;  //just return false to invalidate class and there is an error

    public:
        cwater_reading(std::string time, std::string consumption); //here is the fuctions we can call cause they're closely linked to class::Cwater_reading
        tm get_date();
        float get_consum() const;      //using get_var to access a value in a private property of this class
        bool isRight();
};
#endif // CWATER_READING_H
