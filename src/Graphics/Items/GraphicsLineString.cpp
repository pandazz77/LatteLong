#include "GraphicsLineString.h"

#include "GeometryConvertor.h"

GraphicsLineString::GraphicsLineString(GraphicsItem *parent) : GraphicsPath(parent) {}
GraphicsLineString::GraphicsLineString(const LineString &line, GraphicsItem *parent) : GraphicsLineString(parent){
    setLine(line);
}

void GraphicsLineString::setLine(const LineString &line){
    _line = line;
}

LineString GraphicsLineString::line() const{
    return _line;
}

QPainterPath GraphicsLineString::path(const IProjection *proj) const {
    return GeometryConvertor::line(_line,proj);
}