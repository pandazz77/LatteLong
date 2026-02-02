#include "Latte/Geometry/Polygon.h"

#include <QDebug>


Polygon::Polygon(LineString exterior, QVector<LineString> interiors) 
: exterior(encloseLine(exterior)) {
    for(auto interior: interiors)
        this->interiors.push_back(encloseLine(interior));
}

LineString Polygon::encloseLine(LineString line){
    if(line.cbegin()!=line.cend()) 
        line.push_back(line.front());
    return line;
}

QDebug operator<<(QDebug debug,const Polygon &obj){
    QDebugStateSaver saver(debug);
    debug.nospace() << "Polygon("
    << "\n\texterrior=" << obj.exterior
    << "\n\tinterriors=(\n";
    for(auto interrior: obj.interiors){
        debug << "\t\t" << interrior << "," << "\n";
    }
    debug << "\t)\n";
    debug << ")";
    return debug;
}