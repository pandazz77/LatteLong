#include "Latte/Geometry/Bounds.h"

#include <QDebug>

Bounds::Bounds(const LatLng &ne, const LatLng &sw) 
: northEast(ne), southWest(sw) {
    
}

double wrapLongitude(double lng) {
    while (lng > 180.0) lng -= 360.0;
    while (lng <= -180.0) lng += 360.0;
    return lng;
}

LatLng Bounds::center() const{
    double centerLat = (northEast.lat() + southWest.lat()) / 2.0;

    double west = southWest.lng();
    double east = northEast.lng();

    double centerLng;
    if (east < west) {
        centerLng = (west + (east + 360.0)) / 2.0;
        centerLng = wrapLongitude(centerLng);
    } else {
        centerLng = (west + east) / 2.0;
    }

    return LatLng(centerLat, centerLng);

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