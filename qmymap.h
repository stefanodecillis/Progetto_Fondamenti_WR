#ifndef QMYMAP_H
#define QMYMAP_H


#include <string>
#include <vector>
#include "cwater_reading.h"
#include "input_file.h"
#include <QSignalMapper>
#include <QHash>

class QMyMap : public QSignalMapper
{
Q_OBJECT

public:
    explicit QMyMap(QObject *parent = 0); //Constructor
    /* QSignalMapper methods. This class works exactly the same way */
    void setMapping(QObject *sender, std::map<std::__1::string, std::vector<cwater_reading *> > *water_db);
    void removeMappings(QObject *sender);

    /* HashTable to associate my button with my object */
    QHash<QObject *, std::map<std::string, std::vector<cwater_reading*>>*> assocHash;

Q_SIGNALS: /* Signals to emit */
    void mapped(std::map<std::string, std::vector<cwater_reading*>>*);
public slots:
    void senderDestroyed() {
        removeMappings(sender());
    }
    void map(QObject *sender);
    void map();
    void map_qstring(const QString);

};

#endif // QMYMAP_H
