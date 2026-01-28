#include "LGraphicsItem.h"

MapGraphicsScene *LGraphicsItem::scene() const {
    return dynamic_cast<MapGraphicsScene*>(QGraphicsItem::scene());
}

const IProjection *LGraphicsItem::projection() const {
    if(scene())
        return scene()->projection();
    return nullptr;
}

void LGraphicsItem::addTo(MapGraphicsScene *scene) {
    scene->addItem(this);
}

void LGraphicsItem::addTo(MapGraphicsView *view) {
    addTo(view->scene());
}

void LGraphicsItem::sceneChanged(){

}

void LGraphicsItem::projectionChanged(){
    
}