#pragma once

#include "LatLng.h"
#include <QVector>

class LineString: public QVector<LatLng>{
    public:
        using QVector<LatLng>::QVector;
};