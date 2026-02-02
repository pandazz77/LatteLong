#pragma once

#include "Latte/Geometry/MultiGeometry.h"

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

LatLng LngLat(double lng = 0, double lat = 0);

QDebug operator<<(QDebug debug,const LatLng &obj);

using MultiPoint = MultiGeometry<LatLng>;