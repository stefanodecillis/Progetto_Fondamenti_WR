#include "qmymap.h"

using namespace std;

QMyMap::QMyMap(QObject *parent) : QSignalMapper(parent)
{
}

void QMyMap::setMapping(QObject *sender, std::map<std::string, std::vector<cwater_reading*>>* water_db) {
    assocHash.insert(sender, water_db);
    cout << "Insert: " << water_db << endl;
    connect(sender, SIGNAL(destroyed()), this, SLOT(senderDestroyed()));

}



void QMyMap::map(QObject *sender) {
    if (assocHash.contains(sender)) {
        cout << "Read: " << assocHash.value(sender) << endl;
        emit mapped(assocHash.value(sender));
    }
}

void QMyMap::map() {
    map(sender());
}

/* Map function with qstring */

