#include "MapGraphicsScene.h"

#include "SimpleProjection.h"
#include "GeometryConvertor.h"

MapGraphicsScene::MapGraphicsScene(IProjection *proj, QObject *parent) : QGraphicsScene(parent), _proj(proj) {
            
}

MapGraphicsScene::MapGraphicsScene(QObject *parent) : MapGraphicsScene(new SimpleProjection,parent) {

}

MapGraphicsScene::~MapGraphicsScene() {

}

const IProjection *MapGraphicsScene::projection(){
    return _proj;
}

void MapGraphicsScene::setProjection(IProjection *proj){
    if(_proj)
        delete _proj;
    _proj = proj;
    update();
    setSceneRect(GeometryConvertor::bounds(_proj->bounds(),_proj));
}