#include "GraphicsLineString.h"

#include "GeometryConvertor.h"

GraphicsLineString::GraphicsLineString(GraphicsItem *parent) : GraphicsPath(parent) {}
GraphicsLineString::GraphicsLineString(const LineString &line, GraphicsItem *parent) : GraphicsLineString(parent){
    setLine(line);
}

void GraphicsLineString::setLine(const LineString &line){
    _line = line;
    updatePathCache();
}

LineString GraphicsLineString::line() const{
    return _line;
}

QPainterPath GraphicsLineString::path(const IProjection *proj) const {
    return GeometryConvertor::line(_line,proj);
}

// =========================

GraphicsMultiLineString::GraphicsMultiLineString(GraphicsItem *parent) : TypedGraphicsGroup<GraphicsLineString>(parent){

}

GraphicsMultiLineString::GraphicsMultiLineString(const MultiLineString &lines, GraphicsItem *parent ): GraphicsMultiLineString(parent){
    setLines(lines);
}


void GraphicsMultiLineString::setLines(const MultiLineString &lines){
    // cleanup. TODO: remove
    for(auto grLine: items()){
        remove(grLine,true);
        delete grLine;
    }

    for(auto line: lines){
        GraphicsLineString *item = new GraphicsLineString(line);
        add(item);
        item->setPen(pen());
    }
}

MultiLineString GraphicsMultiLineString::lines() const{
    MultiLineString result;
    for(auto grLine: items()){
        result.push_back(grLine->line());
    }
    return result;
}

void GraphicsMultiLineString::setPen(const QPen &pen) {
    IGraphicsLine::setPen(pen);
    for(auto item: items()) item->setPen(pen);
}