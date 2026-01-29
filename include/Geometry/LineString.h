#pragma once

#include "LatLng.h"
#include "MultiGeometry.h"

#include <QVector>

class LineString: public QVector<LatLng>{
    public:
        using QVector<LatLng>::QVector;
};

using MultiLineString = MultiGeometry<LineString>;