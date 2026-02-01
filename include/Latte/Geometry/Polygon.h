#pragma once

#include "Latte/Geometry/LineString.h"
#include "Latte/Geometry/MultiGeometry.h"

class Polygon{
    public:
        Polygon(LineString exterior = {}, QVector<LineString> interiors = {});

        // returns LinearRing
        static LineString encloseLine(LineString line);

    public:
        LineString exterior;
        QVector<LineString> interiors;
};

using MultiPolygon = MultiGeometry<Polygon>;