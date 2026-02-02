#pragma once

#include "Latte/Geometry/LatLng.h"

struct Bounds{
    Bounds(const LatLng &ne, const LatLng &sw);

    LatLng northEast;
    LatLng southWest;

    LatLng center() const;
    LatLng N() const;
    LatLng NE() const;
    LatLng E() const;
    LatLng SE() const;
    LatLng S() const;
    LatLng SW() const;
    LatLng W() const;
    LatLng NW() const;

};

QDebug operator<<(QDebug debug,const Bounds &obj);