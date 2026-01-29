#include "GraphicsGroup.h"

GraphicsGroup::GraphicsGroup(GraphicsItem* parent) : GraphicsItem(parent) {
    // ItemHasNoContents  for boundingRect and shape by childs
    setFlag(QGraphicsItem::ItemHasNoContents, true);
}

void GraphicsGroup::add(GraphicsItem *item) {
    item->setParentItem(this);
}

void GraphicsGroup::remove(GraphicsItem *item, bool removeFromScene){
    item->setParentItem(nullptr);
    if(removeFromScene && scene()) 
        scene()->removeItem(item);
}

QList<GraphicsItem*> GraphicsGroup::items() const {
    auto base = QGraphicsItem::childItems();
    QList<GraphicsItem*> result;
    for(auto item: base) result.push_back(dynamic_cast<GraphicsItem*>(item));
    return result;
}

// compute by childs
QRectF GraphicsGroup::boundingRect() const {
    if (childItems().isEmpty())
        return QRectF();

    QRectF rect;
    for (const QGraphicsItem* child : childItems())
    {
        // mapRectFromParent is important
        QRectF childRect = mapRectFromParent(child->boundingRect());
        rect |= childRect;
    }
    return rect;
}

// compute by childs
QPainterPath GraphicsGroup::shape() const {
    QPainterPath path;
    for (const QGraphicsItem* child : childItems()) {
        QPainterPath childShape = mapFromItem(child, child->shape());
        path.addPath(childShape);
    }
    return path;
}

// paint empty cuz ItemHasNoContents
void GraphicsGroup::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

bool GraphicsGroup::isObscuredBy(const QGraphicsItem* item) const {
    return QGraphicsItem::isObscuredBy(item);
}

QPainterPath GraphicsGroup::opaqueArea() const {
    return shape();
}