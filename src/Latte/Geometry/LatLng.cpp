#include "Latte/Geometry/LatLng.h"

#include <QDebug>

LatLng::LatLng(double lat, double lng) : _lat(lat), _lng(lng) {}

void LatLng::setLat(double lat){
    _lat = lat;
}

void LatLng::setLng(double lng){
    _lng = lng;
}

double LatLng::lat() const {
    return _lat;
}

double LatLng::lng() const {
    return _lng;
}

LatLng LngLat(double lng, double lat){
    return LatLng(lat,lng);
}

QDebug operator<<(QDebug debug,const LatLng &obj){
    QDebugStateSaver saver(debug);
    debug.nospace() << "LatLng(" << obj.lat() << "," << obj.lng() << ")";
    return debug;
}