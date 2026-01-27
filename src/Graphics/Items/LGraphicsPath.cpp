#include "LGraphicsPath.h"


LGraphicsPath::LGraphicsPath(LGraphicsItem *parent): LGraphicsShape(parent){

}

QRectF LGraphicsPath::boundingRect() const {
    return projectedPath().boundingRect()
            .adjusted(-pen().widthF()/2, -pen().widthF()/2,
                        pen().widthF()/2, pen().widthF()/2);
}

void LGraphicsPath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawPath(projectedPath());
}

QPainterPath LGraphicsPath::shape() const {
    QPainterPathStroker stroker;
    stroker.setWidth(pen().widthF());
    stroker.setCapStyle(pen().capStyle());
    stroker.setJoinStyle(pen().joinStyle());
    return stroker.createStroke(projectedPath());
}


bool LGraphicsPath::contains(const QPointF &point) const {
    return projectedPath().contains(point);
}

QPainterPath LGraphicsPath::projectedPath() const {
    return path(projection());
}