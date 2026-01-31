#include "GraphicsPath.h"


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
    return path(projection());
}

int GraphicsPath::type() const {
    // Enable the use of qgraphicsitem_cast with this item.
    return Type;
}