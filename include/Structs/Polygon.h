#pragma once

#include "LineString.h"

class Polygon{
    public:
        Polygon(LineString exterior = {}, QVector<LineString> interiors = {});

        // returns LinearRing
        static LineString encloseLine(LineString line);

    public:
        LineString exterior;
        QVector<LineString> interiors;
};