#include "input_file.h"
#include <Qstring>
#include<qmessagebox.h>
#include <math.h>
#include <time.h>
#include<fstream>
#include<qdebug.h>
#include<QDateTime>
#include<QDate>
#include<QTime>
#include<qprogressdialog.h>



bool input_file::read_file(std::map<std::string,std::vector<water_reading*>> &reading_map, std::string path, QProgressDialog *loadingwindow) {
    //open file input
    std::ifstream input(path);
clock_t start, end;
start = clock();
 std::string line;
unsigned long counter=0;
unsigned long bytes_totali = (allBytes(path)/1000);
unsigned long bytes_letti = 0;
loadingwindow->setMaximum(bytes_totali);


    if(!input.is_open()) {           //
        qDebug() <<  "ERRORE";    // file not found
        QMessageBox msgBox;
        msgBox.setText("Errore File!");
        msgBox.exec();
        return false;                //
    }

    while(!input.eof()) {

        std::getline(input,line);        // as long as file is not finished, read each line
        if (!fill_in(line,reading_map)){    // open function to check parameters and save them in data structure
            return false;             //check it is valid
        }
//.. ogni carattere della stringa è un byte
        if(loadingwindow->wasCanceled()){
            QMessageBox msgBox;
            msgBox.setText("E' stato bloccato il caricamento..");
            msgBox.exec();
            break;
            return false;
        }
        counter++;
        if (counter==1000) {
            bytes_letti = bytes_letti+(line.length());
            loadingwindow->setValue(bytes_letti);
             counter=0;
        }
    }

    //caso finito
    loadingwindow->setValue(bytes_totali);


    //close file input
    input.close();
    end = clock();

    std::cout << "finito!! Tempo impiegato:";
    std::cout << roundf((float(end - start) / CLOCKS_PER_SEC) * 100) / 100 << std::endl;
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
    id = temp;
    water_reading* newRec = new water_reading(time,consumo);   //i'm not deleting this instance cause iwill need it throughout the program
    reading_map[id].push_back(newRec); //push back water reading in readings vector

    // i'm not deleting this instance cause it will be used throughout this program
    return true;
}

unsigned long input_file::allBytes(std::string path) {
    std::ifstream input(path, std::ifstream::ate | std::ifstream::binary);
    return input.tellg();
}






