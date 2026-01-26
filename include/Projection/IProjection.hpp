#pragma once

#include "LatLng.hpp"
#include <QPointF>

class IProjection{
    public:
        virtual QPointF project(const LatLng &latlng) const = 0;
        virtual LatLng unproject(const QPointF &point) const = 0;
};

