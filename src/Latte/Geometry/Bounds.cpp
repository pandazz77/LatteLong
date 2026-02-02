#include "Latte/Geometry/Bounds.h"

#include <QDebug>

Bounds::Bounds(const LatLng &ne, const LatLng &sw) 
: northEast(ne), southWest(sw) {
    
}

QDebug operator<<(QDebug debug,const Bounds &obj){
    QDebugStateSaver saver(debug);
    debug.nospace() << "Bounds("
        << "NE=" << obj.northEast
        << ",SW=" << obj.southWest
        << ")";
    return debug;
}