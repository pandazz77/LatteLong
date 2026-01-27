#pragma once

#include "LGraphicsPath.hpp"
#include "Polygon.h"
#include "GeometryConvertor.h"

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