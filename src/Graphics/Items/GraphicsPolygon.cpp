#include "GraphicsPolygon.h"
#include "GeometryConvertor.h"

GraphicsPolygon::GraphicsPolygon(GraphicsItem *parent) : GraphicsPath(parent) {}
GraphicsPolygon::GraphicsPolygon(const Polygon &poly, GraphicsItem *parent) : GraphicsPolygon(parent){
    setPolygon(poly);
}

void GraphicsPolygon::setPolygon(const Polygon &poly){
    _poly = poly;
}

Polygon GraphicsPolygon::polygon() const{
    return _poly;
}

QPainterPath GraphicsPolygon::path(const IProjection *proj) const {
    return GeometryConvertor::polygon(_poly,proj);
}