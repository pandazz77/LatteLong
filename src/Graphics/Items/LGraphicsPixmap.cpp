#include "LGraphicsPixmap.h"

#include "GeometryConvertor.h"

LGraphicsPixmap::LGraphicsPixmap(LGraphicsItem *parent) : LGraphicsItem(parent){
    setFlags(QGraphicsItem::ItemIgnoresTransformations); // DOESNT WORK
}

LGraphicsPixmap::LGraphicsPixmap(const QPixmap &pixmap, LGraphicsItem *parent) : LGraphicsItem(parent), _pixmap(pixmap), _offset(0, 0) {

}

void LGraphicsPixmap::setPixmap(const QPixmap &pixmap) {
    prepareGeometryChange();
    _pixmap = pixmap;
}

QPixmap LGraphicsPixmap::pixmap() const {
    return _pixmap;
}

void LGraphicsPixmap::setOffset(const QPointF &offset) {
    if(_offset==offset) 
        return;
    prepareGeometryChange();
    _offset = offset;
}

void LGraphicsPixmap::setOffset(qreal x, qreal y) {
    setOffset(QPointF(x, y));
}

QPointF LGraphicsPixmap::offset() const {
    return _offset;
}

QRectF LGraphicsPixmap::boundingRect() const {
    QPointF projected = projectedPos();

    return QRectF(projected.x() - _offset.x(),
                  projected.y() - _offset.y(),
                  _pixmap.width(),
                  _pixmap.height());
}

void LGraphicsPixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPointF pos = boundingRect().topLeft();

    if (!_pixmap.isNull()) {
        painter->drawPixmap(pos, _pixmap);
    }
}

QPainterPath LGraphicsPixmap::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

bool LGraphicsPixmap::contains(const QPointF &point) const {
    return boundingRect().contains(point);
}

void LGraphicsPixmap::setPos(const LatLng &pos){
    _pos = pos;
}

LatLng LGraphicsPixmap::pos() const{
    return _pos;
}

QPointF LGraphicsPixmap::projectedPos() const {
    return GeometryConvertor::point(_pos,projection());
}
