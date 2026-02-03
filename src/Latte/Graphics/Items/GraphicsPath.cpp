#include "Latte/Graphics/Items/GraphicsPath.h"


GraphicsPath::GraphicsPath(GraphicsItem *parent): GraphicsItem(parent){

}

QRectF GraphicsPath::boundingRect() const {
    return projectedPath().boundingRect()
            .adjusted(-pen().widthF()/2, -pen().widthF()/2,
                        pen().widthF()/2, pen().widthF()/2);
}

void GraphicsPath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(pen());
    painter->drawPath(projectedPath());
}

QPainterPath GraphicsPath::shape() const {
    QPainterPathStroker stroker;
    stroker.setWidth(pen().widthF());
    stroker.setCapStyle(pen().capStyle());
    stroker.setJoinStyle(pen().joinStyle());
    return stroker.createStroke(projectedPath());
}


bool GraphicsPath::contains(const QPointF &point) const {
    return projectedPath().contains(point);
}

QPainterPath GraphicsPath::projectedPath() const {
    return _projectedPathCache;
}

void GraphicsPath::updatePathCache(){
    if(projection()){
        /*
            projected it is QPainterPath in world coordinates.
            We need to extract topLeft position, set it as a QGraphicsItem pos
            and translate projected path to it.
        */
        QPainterPath projected = path(projection());
        QRectF bounds = projected.boundingRect();
        QPointF _pos = bounds.topLeft();
        setPos(_pos);
        _projectedPathCache = projected.translated(-_pos);
    }
}

void GraphicsPath::sceneChanged() {
    GraphicsItem::sceneChanged();
    updatePathCache();
}

void GraphicsPath::projectionChanged() {
    GraphicsItem::projectionChanged();
    updatePathCache();
}
