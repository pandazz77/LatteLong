#pragma once

#include <QPointF>

class LocalCoordinateSystem{
    public:
        QPointF toLocal(QPointF globalPos) const;
        QPointF fromLocal(QPointF localPos) const;
};