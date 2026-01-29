#pragma once

#include "GraphicsPath.h"
#include "Polygon.h"
#include "TypedGraphicsGroup.hpp"

class GraphicsPolygon: public GraphicsPath, public IGraphicsShape{
    public:
        GraphicsPolygon(GraphicsItem *parent = nullptr);
        GraphicsPolygon(const Polygon &poly, GraphicsItem *parent = nullptr);

        void setPolygon(const Polygon &poly);
        Polygon polygon() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
        QPainterPath path(const IProjection *proj) const override;

    private:
        Polygon _poly;
};

class GraphicsMultiPolygon: public TypedGraphicsGroup<GraphicsPolygon>, public IGraphicsShape, public IGraphicsLine{
    public:
        GraphicsMultiPolygon(GraphicsItem *parent = nullptr);
        GraphicsMultiPolygon(const MultiPolygon &polys, GraphicsItem *parent = nullptr);

        void setPen(const QPen &pen) override;
        void setBrush(const QBrush &brush) override;

        void setPolygons(const MultiPolygon &polygons);
        MultiPolygon polygons() const;
};