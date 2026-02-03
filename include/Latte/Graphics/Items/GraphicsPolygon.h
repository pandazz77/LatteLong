#pragma once

#include "Latte/Graphics/Items/GraphicsPath.h"
#include "Latte/Graphics/Items/TypedGraphicsGroup.hpp"
#include "Latte/Geometry/Polygon.h"


class GraphicsPolygon: public GraphicsPath, public IGraphicsShape{
    public:
        enum { Type = BaseType + 4 };
        GraphicsPolygon(GraphicsItem *parent = nullptr);
        GraphicsPolygon(const Polygon &poly, GraphicsItem *parent = nullptr);

        void setPolygon(const Polygon &poly);
        Polygon polygon() const;

        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
        QPainterPath path(const IProjection *proj) const override;

        int type() const override;

    private:
        Polygon _poly;
};

class GraphicsMultiPolygon: public TypedGraphicsGroup<GraphicsPolygon>, public IGraphicsShape, public IGraphicsLine{
    public:
        enum { Type = GroupTypeOffset + GraphicsPolygon::Type };
        GraphicsMultiPolygon(GraphicsItem *parent = nullptr);
        GraphicsMultiPolygon(const MultiPolygon &polys, GraphicsItem *parent = nullptr);

        void setPen(const QPen &pen) override;
        void setBrush(const QBrush &brush) override;

        void setPolygons(const MultiPolygon &polygons);
        MultiPolygon polygons() const;

        int type() const override;
};