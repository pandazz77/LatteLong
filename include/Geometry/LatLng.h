#pragma once

#include "MultiGeometry.h"

class LatLng{
    public:
        LatLng(double lat = 0, double lng = 0);

        void setLat(double lat);
        void setLng(double lng);
        double lat() const;
        double lng() const;

    private:
        double _lat;
        double _lng;
};

inline LatLng LngLat(double lng = 0, double lat = 0);

using MultiPoint = MultiGeometry<LatLng>;