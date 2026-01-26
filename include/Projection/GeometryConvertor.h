#pragma once

#include <QPainterPath>

#include "IProjection.hpp"
#include "LineString.hpp"
#include "Polygon.hpp"

namespace GeometryConvertor{
    QPointF point(const LatLng &latlng, const IProjection *proj);
    QVector<QPointF> simpleLine(const LineString &line, const IProjection *proj);
    QPainterPath line(const LineString &line, const IProjection *proj);
    QPainterPath polygon(const Polygon &poly, const IProjection *proj);
    
    bool isClockwise(const QPolygonF &poly);
    QPolygonF reversePolygon(const QPolygonF &poly);
    QPolygonF ensurePolygonOrder(const QPolygonF &poly, bool clockwise);
    
};