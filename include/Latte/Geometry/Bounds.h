#pragma once

#include "Latte/Geometry/LatLng.h"

struct Bounds{
    Bounds(const LatLng &ne, const LatLng &sw);

    LatLng northEast;
    LatLng southWest;
};