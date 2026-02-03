#pragma once

#include "Latte/Projection/IProjection.hpp"

// Used by the EPSG:3395 CRS
class Mercator: public IProjection{
    public:
        QPointF project(const LatLng &latlng) const override;
        LatLng unproject(const QPointF &point) const override;

        Bounds bounds() const override;

        static constexpr double EARTH_RADIUS = 6378137;
        static constexpr double EARTH_RADIUS_MINOR = 6356752.314245179;

};