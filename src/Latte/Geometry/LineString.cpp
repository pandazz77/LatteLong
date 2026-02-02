#include "Latte/Geometry/LineString.h"

#include <QDebug>

QDebug operator<<(QDebug debug,const LineString &obj){
    QDebugStateSaver saver(debug);
    QStringList positions;
    for(auto p: obj){
        positions.push_back(QString("(%1,%2)").arg(p.lat()).arg(p.lng()));
    }

    debug.nospace().noquote() << "LineString(" 
        << positions.join(", ")
        << ")";
    return debug;
}