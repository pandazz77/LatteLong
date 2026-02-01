#include "Latte/Graphics/Items/GraphicsItem.h"
#include "Latte/Projection/GeometryConvertor.h"

MapGraphicsScene *GraphicsItem::scene() const {
    return dynamic_cast<MapGraphicsScene*>(QGraphicsItem::scene());
}

const IProjection *GraphicsItem::projection() const {
    if(scene())
        return scene()->projection();
    return nullptr;
}

void GraphicsItem::addTo(MapGraphicsScene *scene) {
    scene->addItem(this);
}

void GraphicsItem::addTo(MapGraphicsView *view) {
    addTo(view->scene());
}

void GraphicsItem::sceneChanged(){
    updateScenePos();
}

void GraphicsItem::projectionChanged(){
    updateScenePos();
}

void GraphicsItem::updateScenePos(){
    setPos(GeometryConvertor::point(_geoPos,projection()));
}

void GraphicsItem::setGPos(const LatLng &geoPos){
    _geoPos = geoPos;
    if(scene())
        updateScenePos();
}

LatLng GraphicsItem::gPos() const {
    return _geoPos;
};