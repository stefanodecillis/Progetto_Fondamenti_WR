#include "cwater_reading.h"

cwater_reading::cwater_reading(std::string time, std::string consumption) {
    consum = stof(consumption);
    std::string temp;
    int year, month, day ,hour,min,sec;
    bool yearFound = false, hourFound = false;
    for (size_t i = 0; i<time.size();++i){
        if (time[i] >= '0' && time[i] <='9'){
            temp += time[i];
        }
        else if (time[i]== '-' && yearFound == false){
            year=stoi(temp);
            temp.clear();
            yearFound = true;
        }
        else if (time[i] == '-' && yearFound == true){
            month=stoi(temp);
            temp.clear();
        }
        else if (time[i] == ' '){
            day = stoi(temp);
            temp.clear();
        }
        else if (time[i] == ':'&& hourFound == false){
            hour == stoi(temp);
            temp.clear();
            hourFound = true;
        }
        else if (time[i] == ':'&& hourFound == true){
            min = stoi(temp);
            temp.clear();
        }
        else if (time[i] == '"'){} //do nothing
    }
    sec = stoi(temp);
    date.tm_sec = sec;
    date.tm_min = min;
    //date.tm_hour = hour;
    date.tm_mday = day;
    date.tm_mon = month;
    date.tm_year = year;
}


bool cwater_reading::isRight() {
    return findError;
}

tm cwater_reading::get_date() {
    return date;
}

float cwater_reading::get_consum() const{
    return consum;
}





