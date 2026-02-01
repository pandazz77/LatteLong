#pragma once

#include "Latte/Geometry/LatLng.h"
#include "Latte/Geometry/MultiGeometry.h"

#include <QVector>

class LineString: public QVector<LatLng>{
    public:
        using QVector<LatLng>::QVector;
};

using MultiLineString = MultiGeometry<LineString>;