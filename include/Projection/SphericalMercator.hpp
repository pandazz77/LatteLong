#pragma once

#include "IProjection.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

// Used by the EPSG:3857 CRS
class SphericalMercator: public IProjection{
    public:
        QPointF project(const LatLng &latlng) const override {
            const double d = M_PI / 180,
            max = MAX_LATITUDE,
            lat = std::max(std::min(max,latlng.lat()),-max),
            lsin = sin(lat * d);
        
            return QPointF(
                EARTH_RADIUS * latlng.lng() * d,
                EARTH_RADIUS * log((1 + lsin) / (1 - lsin)) / 2
            );
        }

        LatLng unproject(const QPointF &point) const override {
            const double d = 180 / M_PI;

            return LatLng(
                (2 * atan(exp(point.y() / EARTH_RADIUS)) - (M_PI / 2)) * d,
                point.x() * d / EARTH_RADIUS
            );
        }

        static constexpr double EARTH_RADIUS = 6378137;
        static constexpr double MAX_LATITUDE = 85.0511287798;

};