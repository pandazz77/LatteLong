#include "LGraphicsLineString.h"

LGraphicsLineString::LGraphicsLineString(LGraphicsItem *parent) : LGraphicsPath(parent) {}
LGraphicsLineString::LGraphicsLineString(const LineString &line, LGraphicsItem *parent) : LGraphicsLineString(parent){
    setLine(line);
}

void LGraphicsLineString::setLine(const LineString &line){
    _line = line;
}

LineString LGraphicsLineString::line() const{
    return _line;
}

QPainterPath LGraphicsLineString::path(const IProjection *proj) const {
    return GeometryConvertor::line(_line,proj);
}