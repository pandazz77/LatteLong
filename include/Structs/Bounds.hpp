#pragma once

#include "LatLng.hpp"

struct Bounds{
    Bounds(const LatLng &ne, const LatLng &sw) : northEast(ne), southWest(sw) {
        
    }

    LatLng northEast;
    LatLng southWest;
};