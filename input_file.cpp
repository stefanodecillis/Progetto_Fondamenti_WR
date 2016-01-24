#include "input_file.h"
#include <Qstring>
#include<qmessagebox.h>





input_file::input_file(QObject *parent):
QObject(parent)
{


}

bool input_file::read_file(std::map<std::string,std::vector<water_reading*>> &reading_map,std::string path) {
    //open file input
    std::ifstream input(path);

    if(!input.is_open()) {           //
        std::cout << "ERRORE" << std::endl;    // file not found
        return false;                //
    }

    while(!input.eof()) {
        std::string line;
        std::getline(input,line);        // as long as file is not finished, read each line
        if (!fill_in(line,reading_map)){    // open function to check parameters and save them in data structure
            return false;             //check it is valid
        }
    }


    //close file input
    input.close();
    return true;
}

bool input_file::fill_in(const std::string &line, std::map<std::string, std::vector<water_reading *> > &reading_map){
    bool timeFound = false;
    std::string time,id,temp,consumo;                       //creo variabili che mi serviranno come appoggio
    for (size_t i = 0; i < line.size();++i){     //scorro la stringa

        if (line[i] == ',' && timeFound == false) { //ho trovato ','
            time = temp;      // salvo temp in data
            temp.clear();       //pulisco temp per la prossima operazione
            timeFound = true;       //ho trovato la data
        }

        else if (line[i] == ',' && timeFound == true) {
            consumo = temp;  // converto stringa del consumo in double
            temp.clear();         //pulisco variabile di appoggio
        }
        else if (line[i] == '.'|| line[i] == ':'|| line[i] == '-'|| line[i] == '"'||(line[i] >= 'A' && line[i] <= 'Z') ||
                 ( line[i] >= 'a' && line[i] <= 'z') || line[i] == ' '||(line[i]>= 48 && line[i] <= '9'))
        {temp += line[i];} //salva i caratteri che mi servono
        else{
            std::cout << "Errore nel file input -> caratteri non corretti"<< std::endl;
            return false;
        }
    }
    id = temp;    //set id
    water_reading* reading = new water_reading(time,consumo);   //new water_reading         //REMEMBER STRING DATE IS WITHIN  ""YYYY-MM....."\"
     reading_map[id].push_back(reading); //push back water reading in readings vector

    // i'm not deleting this instance cause it will be used throughout this program

    return true;
}

void input_file::setValue(QString str){ //stampa quello passato dal sender, qui esplicito un nome della variabile
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();

}

