#include "Latte/Graphics/Items/GraphicsPixmap.h"

IGraphicsPixmap::IGraphicsPixmap(const QPixmap &pixmap) : _pixmap(pixmap){

}


void IGraphicsPixmap::setPixmap(const QPixmap &pixmap){
    _pixmap = pixmap;
}
QPixmap IGraphicsPixmap::pixmap() const{
    return _pixmap;
}

void IGraphicsPixmap::setOffset(const QPointF &offset){
    _offset = offset;
}
QPointF IGraphicsPixmap::offset() const{
    return _offset;
}

void IGraphicsPixmap::setAnchor(const QPointF &anchor){
    setOffset(-anchor);
}
QPointF IGraphicsPixmap::anchor(){
    return -offset();
}

// ==========================

GraphicsPixmap::GraphicsPixmap(const QPixmap &pixmap, GraphicsItem *parent) : GraphicsItem(parent), IGraphicsPixmap(pixmap) {
    QGraphicsItem::setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
}

GraphicsPixmap::GraphicsPixmap(GraphicsItem *parent) : GraphicsPixmap({},parent){

}

void GraphicsPixmap::setPixmap(const QPixmap &pixmap) {
    prepareGeometryChange();
    IGraphicsPixmap::setPixmap(pixmap);
}


void GraphicsPixmap::setOffset(const QPointF &offset) {
    prepareGeometryChange();
    IGraphicsPixmap::setOffset(offset);
}

QRectF GraphicsPixmap::boundingRect() const {
    if(pixmap().isNull()) return QRectF();

    return QRectF(offset(), pixmap().size());
}

void GraphicsPixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!pixmap().isNull()) {
        painter->drawPixmap(offset(), pixmap());
    }
}

QPainterPath GraphicsPixmap::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

bool GraphicsPixmap::contains(const QPointF &point) const {
    return boundingRect().contains(point);
}

// ===============================

GraphicsMultiPixmap::GraphicsMultiPixmap(const QPixmap &pixmap, const MultiPoint &points, GraphicsItem *parent) : TypedGraphicsGroup<GraphicsPixmap>(parent), IGraphicsPixmap(pixmap) {
    setPoints(points);
}

GraphicsMultiPixmap::GraphicsMultiPixmap(GraphicsItem *parent) : GraphicsMultiPixmap({},{},parent) {
    
}

void GraphicsMultiPixmap::setPixmap(const QPixmap &pixmap){
    IGraphicsPixmap::setPixmap(pixmap);
    for(auto item: items()) item->setPixmap(pixmap);
}

void GraphicsMultiPixmap::setOffset(const QPointF &offset){
    IGraphicsPixmap::setOffset(offset);
    for(auto item: items()) item->setOffset(offset);
}

void GraphicsMultiPixmap::setAnchor(const QPointF &anchor){
    IGraphicsPixmap::setAnchor(anchor);
    for(auto item: items()) item->setAnchor(anchor);
}


void GraphicsMultiPixmap::setPoints(const MultiPoint &points){
    // cleanup. TODO: remove
    for(auto grPixmap: items()){
        remove(grPixmap,true);
        delete grPixmap;
    }

    for(auto point: points){
        GraphicsPixmap *item = new GraphicsPixmap(pixmap());
        add(item);
        item->setOffset(offset());
        item->setGPos(point);
    }
}

MultiPoint GraphicsMultiPixmap::points() const {
    MultiPoint result;
    for(auto grPixmap: items()){
        result.push_back(grPixmap->gPos());
    }
    return result;
}