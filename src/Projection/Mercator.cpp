#include "Mercator.h"

#define _USE_MATH_DEFINES
#include <math.h>

QPointF Mercator::project(const LatLng &latlng) const {
    double x, y;
    const double d = M_PI / 180,
        r = EARTH_RADIUS,
        tmp = EARTH_RADIUS_MINOR / r,
        e = sqrt(1 - tmp * tmp);
    y = latlng.lat() * d;
    const double con = e * sin(y);
    const double ts = tan(M_PI/4-y/2) / pow((1-con)/(1+con),e/2);
    y = -r * log(std::max(ts,1E-10));
    x = latlng.lng() * d * r;
    return QPointF(x,y);
}

LatLng Mercator::unproject(const QPointF &point) const {
    const double d = 180 / M_PI,
        r = EARTH_RADIUS,
        tmp = EARTH_RADIUS_MINOR / r,
        e = sqrt(1 - tmp * tmp),
        ts = exp(-point.y() / r);
    double phi = M_PI / 2 - 2 * atan(ts);

    for(double i = 0, dphi = 0.1, con; i < 15 && abs(dphi) > 1e-7; i++){
        con = e * sin(phi);
        con = pow((1 - con) / (1 + con), e / 2);
        dphi = M_PI / 2 - 2 * atan(ts * con) - phi;
        phi += dphi;
    }

    return LatLng(
        phi * d,
        point.x() * d / r
    );
}

Bounds Mercator::bounds() const{
    return {
        LatLng{84,180},
        LatLng{-80,-180}
    };
}