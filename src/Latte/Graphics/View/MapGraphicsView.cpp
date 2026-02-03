#include "Latte/Graphics/View/MapGraphicsView.h"

#include "Latte/Projection/GeometryConvertor.h"
#include "Latte/Projection/SimpleProjection.h"

MapGraphicsView::MapGraphicsView(MapGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent){
    setDragMode(QGraphicsView::ScrollHandDrag);
}

MapGraphicsView::MapGraphicsView(QWidget *parent) 
: MapGraphicsView(new MapGraphicsScene(new SimpleProjection,nullptr), parent) { // wtf. TODO: deal with construction args

}

MapGraphicsScene *MapGraphicsView::scene() const {
    return dynamic_cast<MapGraphicsScene*>(QGraphicsView::scene());
}

void MapGraphicsView::setProjection(IProjection *proj){
    scene()->setProjection(proj);
    fitBounds();
}

const IProjection *MapGraphicsView::projection() const {
    return scene()->projection();
}

const GeometryConvertor &MapGraphicsView::convertor() const{
    return scene()->convertor();
}

void MapGraphicsView::fitBounds(){
    fitInView(convertor().bounds(projection()->bounds()));
}

void MapGraphicsView::wheelEvent(QWheelEvent *event) {
    int sign = event->angleDelta().y() < 0 ? -1 : 1;
    double zoomFactor = 0.25;
    double zoom = 1+sign*zoomFactor;
    
    scale(zoom,zoom);
}

void MapGraphicsView::showEvent(QShowEvent *event) {
    fitBounds();

    QGraphicsView::showEvent(event);
}