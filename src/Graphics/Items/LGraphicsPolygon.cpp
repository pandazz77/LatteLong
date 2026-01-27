#include "LGraphicsPolygon.h"
#include "GeometryConvertor.h"

LGraphicsPolygon::LGraphicsPolygon(LGraphicsItem *parent) : LGraphicsPath(parent) {}
LGraphicsPolygon::LGraphicsPolygon(const Polygon &poly, LGraphicsItem *parent) : LGraphicsPolygon(parent){
    setPolygon(poly);
}

void LGraphicsPolygon::setPolygon(const Polygon &poly){
    _poly = poly;
}

Polygon LGraphicsPolygon::polygon() const{
    return _poly;
}

QPainterPath LGraphicsPolygon::path(const IProjection *proj) const {
    return GeometryConvertor::polygon(_poly,proj);
}