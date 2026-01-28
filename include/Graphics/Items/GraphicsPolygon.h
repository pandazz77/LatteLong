#pragma once

#include "GraphicsPath.h"
#include "Polygon.h"

class GraphicsPolygon: public GraphicsPath{
    public:
        GraphicsPolygon(GraphicsItem *parent = nullptr);
        GraphicsPolygon(const Polygon &poly, GraphicsItem *parent = nullptr);

        void setPolygon(const Polygon &poly);
        Polygon polygon() const;

        QPainterPath path(const IProjection *proj) const override;

    private:
        Polygon _poly;
};