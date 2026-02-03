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

const GeometryConvertor &GraphicsItem::convertor() const {
    if(scene())
        return scene()->convertor();
    throw std::runtime_error("Cannot get GeometryConvertor due to null scene");
}

void GraphicsItem::addTo(MapGraphicsScene *scene) {
    scene->addItem(this);
}

void GraphicsItem::addTo(MapGraphicsView *view) {
    addTo(view->scene());
}

void GraphicsItem::sceneChanged(){
    if(projection() )
        updateScenePos();
}

void GraphicsItem::projectionChanged(){
    if(projection())
        updateScenePos();
}

// CAN BE SOME COLLISION BETWEEN SCENE POS AND GEOPOS, I DIDNT TEST IT WELL

void GraphicsItem::updateScenePos(){
    QGraphicsItem::setPos(convertor().point(_geoPos));
}

void GraphicsItem::updateGeoPos(){
    _geoPos = convertor().point(pos());
}

void GraphicsItem::setGPos(const LatLng &geoPos){
    _geoPos = geoPos;
    if(scene())
        updateScenePos();
}

void GraphicsItem::setPos(const QPointF &pos){
    QGraphicsItem::setPos(pos);
    if(scene())
        updateGeoPos();
}

void GraphicsItem::setX(double x){
    setPos({x,y()});
}

void GraphicsItem::setY(double y){
    setPos({x(),y});
}

LatLng GraphicsItem::gPos() const {
    return _geoPos;
};

int GraphicsItem::type() const {
    // Enable the use of qgraphicsitem_cast with this item.
    return Type;
}
