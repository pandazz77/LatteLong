#include "LGraphicsPixmap.h"

#include "GeometryConvertor.h"

LGraphicsPixmap::LGraphicsPixmap(const QPixmap &pixmap, LGraphicsItem *parent) : LGraphicsItem(parent), _pixmap(pixmap), _offset(0, 0) {
    QGraphicsItem::setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
}

LGraphicsPixmap::LGraphicsPixmap(LGraphicsItem *parent) : LGraphicsItem(parent){

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
    if(_pixmap.isNull()) return QRectF();

    return QRectF(_offset, _pixmap.size());
}

void LGraphicsPixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!_pixmap.isNull()) {
        painter->drawPixmap(_offset, _pixmap);
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

void LGraphicsPixmap::setGeoPos(const LatLng &pos){
    _pos = pos;
    if(scene()){
        updateScenePos();
    }
}

LatLng LGraphicsPixmap::geoPos() const{
    return _pos;
}

void LGraphicsPixmap::sceneChanged() {
    updateScenePos();
}

void LGraphicsPixmap::projectionChanged() {
    updateScenePos();
}

void LGraphicsPixmap::updateScenePos() {
    setPos(GeometryConvertor::point(_pos,projection()));
}