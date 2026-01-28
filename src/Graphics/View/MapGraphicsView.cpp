#include "MapGraphicsView.h"

#include "GeometryConvertor.h"
#include "SimpleProjection.h"

MapGraphicsView::MapGraphicsView(MapGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent){
    scale(1,-1); // rotate Y axis

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

const IProjection *MapGraphicsView::projection(){
    return scene()->projection();
}

void MapGraphicsView::fitBounds(){
    fitInView(GeometryConvertor::bounds(projection()->bounds(),projection()));
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