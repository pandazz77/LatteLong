#pragma once

#include <Latte/Geometry/LatLng.h>

class FooGeometry{
    public:
        FooGeometry(const LatLng &p1, const LatLng &p2);    

        LatLng p1;
        LatLng p2;
};