#include "SphericalMercator.h"

#define _USE_MATH_DEFINES
#include <math.h>

QPointF SphericalMercator::project(const LatLng &latlng) const {
    const double d = M_PI / 180,
    max = MAX_LATITUDE,
    lat = std::max(std::min(max,latlng.lat()),-max),
    lsin = sin(lat * d);

    return QPointF(
        EARTH_RADIUS * latlng.lng() * d,
        EARTH_RADIUS * log((1 + lsin) / (1 - lsin)) / 2
    );
}

LatLng SphericalMercator::unproject(const QPointF &point) const {
    const double d = 180 / M_PI;

    return LatLng(
        (2 * atan(exp(point.y() / EARTH_RADIUS)) - (M_PI / 2)) * d,
        point.x() * d / EARTH_RADIUS
    );
}

Bounds SphericalMercator::bounds() const {
    return {
        LatLng(85.06,180),
        LatLng(-85.06,-180)
    };
}