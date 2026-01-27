#pragma once

#include "IProjection.hpp"

// Used by the EPSG:3857 CRS
class SphericalMercator: public IProjection{
    public:
        QPointF project(const LatLng &latlng) const override;
        LatLng unproject(const QPointF &point) const override;

        Bounds bounds() const override;

        static constexpr double EARTH_RADIUS = 6378137;
        static constexpr double MAX_LATITUDE = 85.0511287798;

};