#include "LGraphicsItem.h"
#include "GeometryConvertor.h"

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
    updateScenePos();
}

void LGraphicsItem::projectionChanged(){
    updateScenePos();
}

void LGraphicsItem::updateScenePos(){
    setPos(GeometryConvertor::point(_geoPos,projection()));
}

void LGraphicsItem::setGPos(const LatLng &geoPos){
    _geoPos = geoPos;
    if(scene())
        updateScenePos();
}

LatLng LGraphicsItem::gPos() const {
    return _geoPos;
};