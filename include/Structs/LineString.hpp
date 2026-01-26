#pragma once

#include "LatLng.hpp"
#include <QVector>

class LineString: public QVector<LatLng>{
    public:
        using QVector<LatLng>::QVector;
};