#include "GraphicsPixmap.h"

#include "GeometryConvertor.h"

GraphicsPixmap::GraphicsPixmap(const QPixmap &pixmap, GraphicsItem *parent) : GraphicsItem(parent), _pixmap(pixmap), _offset(0, 0) {
    QGraphicsItem::setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
}

GraphicsPixmap::GraphicsPixmap(GraphicsItem *parent) : GraphicsItem(parent){

}

void GraphicsPixmap::setPixmap(const QPixmap &pixmap) {
    prepareGeometryChange();
    _pixmap = pixmap;
}

QPixmap GraphicsPixmap::pixmap() const {
    return _pixmap;
}

void GraphicsPixmap::setOffset(const QPointF &offset) {
    if(_offset==offset) 
        return;
    prepareGeometryChange();
    _offset = offset;
}

QPointF GraphicsPixmap::offset() const {
    return _offset;
}

void GraphicsPixmap::setAnchor(const QPointF &anchor){
    setOffset(-anchor);
}

QPointF GraphicsPixmap::anchor(){
    return -offset();
}


QRectF GraphicsPixmap::boundingRect() const {
    if(_pixmap.isNull()) return QRectF();

    return QRectF(_offset, _pixmap.size());
}

void GraphicsPixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!_pixmap.isNull()) {
        painter->drawPixmap(_offset, _pixmap);
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