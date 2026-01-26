#pragma once

#include "IProjection.hpp"

class SimpleProjection: public IProjection{
    public:
        QPointF project(const LatLng &latlng) const override{
            return QPointF(latlng.lng(),latlng.lat());
        }
        LatLng unproject(const QPointF &point) const override{
            return LatLng(point.y(),point.x());
        }
};