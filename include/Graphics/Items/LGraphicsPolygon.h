#pragma once

#include "LGraphicsPath.h"
#include "Polygon.h"

class LGraphicsPolygon: public LGraphicsPath{
    public:
        LGraphicsPolygon(LGraphicsItem *parent = nullptr);
        LGraphicsPolygon(const Polygon &poly, LGraphicsItem *parent = nullptr);

        void setPolygon(const Polygon &poly);
        Polygon polygon() const;

        QPainterPath path(const IProjection *proj) const override;

    private:
        Polygon _poly;
};