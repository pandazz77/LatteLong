#include "Latte/Geometry/Bounds.h"

#include <QDebug>

Bounds::Bounds(const LatLng &ne, const LatLng &sw) 
: northEast(ne), southWest(sw) {
    
}

LatLng Bounds::center() const{
    return LatLng{
        (northEast.lat() + southWest.lat()) / 2.0,
        (northEast.lng() + southWest.lng()) / 2.0,
    };
}

LatLng Bounds::N() const{
    return LatLng{
        northEast.lat(),
        center().lng()
    };
}

LatLng Bounds::NE() const{
    return northEast;
}

LatLng Bounds::E() const{
    return LatLng{
        center().lat(),
        northEast.lng()
    };
}

LatLng Bounds::SE() const{
    return LatLng{
        southWest.lat(),
        northEast.lng()
    };
}

LatLng Bounds::S() const{
    return LatLng{
        southWest.lat(),
        center().lng(),
    };
}

LatLng Bounds::SW() const{
    return southWest;
}

LatLng Bounds::W() const{
    return LatLng{
        center().lat(),
        southWest.lng()
    };
}

LatLng Bounds::NW() const{
    return LatLng{
        northEast.lat(),
        southWest.lng()
    };
}


QDebug operator<<(QDebug debug,const Bounds &obj){
    QDebugStateSaver saver(debug);
    debug.nospace() << "Bounds("
        << "NE=" << obj.northEast
        << ",SW=" << obj.southWest
        << ")";
    return debug;
}