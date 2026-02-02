#include "Latte/Graphics/Items/GraphicsPolygon.h"
#include "Latte/Projection/GeometryConvertor.h"

GraphicsPolygon::GraphicsPolygon(GraphicsItem *parent) : GraphicsPath(parent) {}
GraphicsPolygon::GraphicsPolygon(const Polygon &poly, GraphicsItem *parent) : GraphicsPolygon(parent){
    setPolygon(poly);
}

void GraphicsPolygon::setPolygon(const Polygon &poly){
    _poly = poly;
    updatePathCache();
}

Polygon GraphicsPolygon::polygon() const{
    return _poly;
}

QPainterPath GraphicsPolygon::path(const IProjection *proj) const {
    return convertor().polygon(_poly);
}

void GraphicsPolygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(brush());
    GraphicsPath::paint(painter,option,widget);
}

// =========================

GraphicsMultiPolygon::GraphicsMultiPolygon(GraphicsItem *parent) : TypedGraphicsGroup<GraphicsPolygon>(parent){

}

GraphicsMultiPolygon::GraphicsMultiPolygon(const MultiPolygon &polygons, GraphicsItem *parent ): GraphicsMultiPolygon(parent){
    setPolygons(polygons);
}


void GraphicsMultiPolygon::setPolygons(const MultiPolygon &polygons){
    // cleanup. TODO: remove
    for(auto grPoly: items()){
        remove(grPoly,true);
        delete grPoly;
    }

    for(auto poly: polygons){
        GraphicsPolygon *item = new GraphicsPolygon(poly);
        add(item);
        item->setPen(pen());
        item->setBrush(brush());
    }
}

void GraphicsMultiPolygon::setPen(const QPen &pen) {
    IGraphicsLine::setPen(pen);
    for(auto item: items()) item->setPen(pen);
}

void GraphicsMultiPolygon::setBrush(const QBrush &brush) {
    IGraphicsShape::setBrush(brush);
    for(auto item: items()) item->setBrush(brush);
}


MultiPolygon GraphicsMultiPolygon::polygons() const{
    MultiPolygon result;
    for(auto grPoly: items()){
        result.push_back(grPoly->polygon());
    }
    return result;
}
