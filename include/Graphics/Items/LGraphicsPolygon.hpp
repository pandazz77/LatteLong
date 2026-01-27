#pragma once

#include "LGraphicsPath.hpp"
#include "Polygon.hpp"
#include "GeometryConvertor.h"

class LGraphicsPolygon: public LGraphicsPath{
    public:
        LGraphicsPolygon(LGraphicsItem *parent = nullptr) : LGraphicsPath(parent) {}
        LGraphicsPolygon(const Polygon &poly, LGraphicsItem *parent = nullptr) : LGraphicsPolygon(parent){
            setPolygon(poly);
        }

        void setPolygon(const Polygon &poly){
            _poly = poly;
        }

        Polygon polygon() const{
            return _poly;
        }

        QPainterPath path(const IProjection *proj) const override {
            return GeometryConvertor::polygon(_poly,proj);
        }

    private:
        Polygon _poly;
};