#pragma once

#include <QPainterPath>

#include "Latte/Projection/LocalCoordinateSystem.h"
#include "Latte/Projection/IProjection.hpp"
#include "Latte/Geometry/LineString.h"
#include "Latte/Geometry/Polygon.h"

class GeometryConvertor{
    public:
        GeometryConvertor(IProjection *rawProjPtr=nullptr);

        void setProjection(IProjection *rawProjPtr);
        const IProjection *projection() const;

        QPointF point(const LatLng &latlng) const;
        QVector<QPointF> simpleLine(const LineString &line) const;
        QPainterPath line(const LineString &line) const;
        QPainterPath polygon(const Polygon &poly) const;
        QRectF bounds(const Bounds &bounds) const;
        
        static bool isClockwise(const QPolygonF &poly);
        static QPolygonF reversePolygon(const QPolygonF &poly);
        static QPolygonF ensurePolygonOrder(const QPolygonF &poly, bool clockwise);

    private:
        std::unique_ptr<IProjection> _proj;
        LocalCoordinateSystem lcs;
};