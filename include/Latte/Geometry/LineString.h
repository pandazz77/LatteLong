#pragma once

#include "Latte/Geometry/LatLng.h"
#include "Latte/Geometry/MultiGeometry.h"

#include <QVector>

class LineString: public QVector<LatLng>{
    public:
        using QVector<LatLng>::QVector;
};

QDebug operator<<(QDebug debug,const LineString &obj);

using MultiLineString = MultiGeometry<LineString>;