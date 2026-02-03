#include "Latte/Projection/LocalCoordinateSystem.h"

// At the moment - local cs is very simple

QPointF LocalCoordinateSystem::toLocal(QPointF globalPos) const {
    globalPos.setY(-globalPos.y());
    return globalPos;
}

QPointF LocalCoordinateSystem::fromLocal(QPointF localPos) const {
    localPos.setY(-localPos.y());
    return localPos;
}