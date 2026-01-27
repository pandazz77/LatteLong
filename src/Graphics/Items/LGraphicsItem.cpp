#include "LGraphicsItem.h"

MapGraphicsScene *LGraphicsItem::scene() const {
    return dynamic_cast<MapGraphicsScene*>(QGraphicsItem::scene());
}

const IProjection *LGraphicsItem::projection() const {
    return scene()->projection();
}

void LGraphicsItem::addTo(MapGraphicsScene *scene) {
    scene->addItem(this);
}

void LGraphicsItem::addTo(MapGraphicsView *view) {
    addTo(view->scene());
}