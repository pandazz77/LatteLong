#pragma once

#include "IProjection.hpp"

// Equirectangular projection / Used by the EPSG:4326 CRS
class SimpleProjection: public IProjection{
    public:
        QPointF project(const LatLng &latlng) const override{
            return QPointF(latlng.lng(),latlng.lat());
        }
        LatLng unproject(const QPointF &point) const override{
            return LatLng(point.y(),point.x());
        }

        Bounds bounds() const override {
            return {
                LatLng(90,180),
                LatLng(-90,-180)
            };
        }
};