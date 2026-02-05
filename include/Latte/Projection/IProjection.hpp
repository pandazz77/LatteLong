#pragma once

#include "Latte/Geometry/LatLng.h"
#include "Latte/Geometry/Bounds.h"

#include <QPointF>

class IProjection{
    public:
        virtual QPointF project(const LatLng &latlng) const = 0;
        virtual LatLng unproject(const QPointF &point) const = 0;
        virtual Bounds bounds() const = 0;
};

