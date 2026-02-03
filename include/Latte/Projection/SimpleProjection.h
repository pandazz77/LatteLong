#pragma once

#include "Latte/Projection/IProjection.hpp"

// Equirectangular projection / Used by the EPSG:4326 CRS
class SimpleProjection: public IProjection{
    public:
        QPointF project(const LatLng &latlng) const override;
        LatLng unproject(const QPointF &point) const override;

        Bounds bounds() const override;
};