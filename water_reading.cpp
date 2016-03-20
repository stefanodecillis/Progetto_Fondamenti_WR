#include "water_reading.h"
#include <iostream>

water_reading::water_reading (float consumption,tm data):consumption(consumption)
{
    this->data.tm_hour = data.tm_hour;
    this->data.tm_mday = data.tm_mday;
    this->data.tm_min = data.tm_min;
    this->data.tm_mon = data.tm_mon;
    this->data.tm_sec = data.tm_sec;
    this->data.tm_year = data.tm_year;
}

water_reading::water_reading(std::string time, std::string consum)
{
   consumption = stof(consum);
   if (!time.empty())
   {
       std::string temp,detime;
       int year, month, day ,hour,min,sec;
       bool yearFound = false, hourFound = false;
           for (size_t i = 0; i<time.size() ; ++i)
           {
               if ((time[i] <= '9' && time[i] >='0') || time[i] == ':')
               {
                   temp += time[i];
               }
               else if (time[i] == '-' && yearFound == false)
               {
                   year = stoi(temp);
                   yearFound = true;
                   temp.clear();
               }
               else if (time[i] == '-' && yearFound == true)
               {
                   month = stoi(temp);
                   temp.clear();
               }
               else if (time[i] == ' ')
               {
                   day = stoi(temp);
                   temp.clear();
               }
           }
           detime = temp;

           temp.clear();
           for (size_t i = 0; i<detime.size() ; i++)
           {
               if ((detime[i] <= '9' && detime[i] >='0') )
               {
                   temp += detime[i];
               }
               else if (detime[i] == ':' &&  hourFound == false)
               {
                   hour = stoi(temp);
                   hourFound = true;
                   temp.clear();
               }
               else if (detime[i] == ':' &&  hourFound == true)
               {
                   min = stoi(temp);
                   temp.clear();
               }
           }
           sec = stoi(temp);
       this->data.tm_year = year;
       this->data.tm_mon = month;
       this->data.tm_mday = day;
       this->data.tm_hour = hour;
       this->data.tm_min = min;
       this->data.tm_sec = sec;
   }
       /*
        inserirli nella struct tm
        */
}

tm water_reading::get_data()
{
    return data;
}

bool water_reading::compare_tm(tm data1,tm data2, int depth)
{
    int firstParam = 0;
    int secondParam = 0;
    switch(depth)
    {
    case 0:
        firstParam = data1.tm_year;
        secondParam = data2.tm_year;
        break;
    case 1:
        firstParam = data1.tm_mon;
        secondParam = data2.tm_mon;
        break;
    case 2:
        firstParam = data1.tm_mday;
        secondParam = data2.tm_mday;
        break;
    default:
        return false;
    }
    if (firstParam < secondParam)
    {
        return true;
    }
    else if (firstParam >secondParam)
    {
        return false;
    }
    else
        return compare_tm(data1,data2, depth+1);

    return false;
}

bool water_reading::compare(water_reading a, int depth)
{
    int firstParam = 0;
    int secondParam = 0;
    switch(depth)
    {
    case 0:
        firstParam = this->get_data().tm_year;
        secondParam = a.get_data().tm_year;
        break;
    case 1:
        firstParam = this->get_data().tm_mon;
        secondParam = a.get_data().tm_mon;
        break;
    case 2:
        firstParam = this->get_data().tm_mday;
        secondParam = a.get_data().tm_mday;
         break;
    case 3:
        firstParam = this->get_data().tm_hour;
        secondParam = a.get_data().tm_hour;
         break;
    case 4:
        firstParam = this->get_data().tm_min;
        secondParam = a.get_data().tm_min;
         break;
    case 5:
        firstParam = this->get_data().tm_sec;
        secondParam = a.get_data().tm_sec;
         break;
    default:
        return false;
    }

    if (firstParam < secondParam)
    {
        return true;
    }
    else if (firstParam >secondParam)
    {
        return false;
    }
    else
        return compare(a, depth+1);

    return false;
}


