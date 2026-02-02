#include "Latte/Graphics/View/MapGraphicsScene.h"

#include "Latte/Projection/SimpleProjection.h"
#include "Latte/Projection/GeometryConvertor.h"
#include "Latte/Graphics/Items/GraphicsItem.h"

MapGraphicsScene::MapGraphicsScene(IProjection *proj, QObject *parent) : QGraphicsScene(parent){
    setProjection(proj);
}

MapGraphicsScene::MapGraphicsScene(QObject *parent) : MapGraphicsScene(new SimpleProjection,parent) {

}

MapGraphicsScene::~MapGraphicsScene() {

}

const GeometryConvertor &MapGraphicsScene::convertor() const {
    return _convertor;
}

const IProjection *MapGraphicsScene::projection(){
    return _proj;
}

void MapGraphicsScene::setProjection(IProjection *proj){
    if(_proj)
        delete _proj;
    _proj = proj;
    _convertor.setProjection(_proj);
    update();
    setSceneRect(_convertor.bounds(_proj->bounds()));
    for(QGraphicsItem *item: items()){
        GraphicsItem *litem = dynamic_cast<GraphicsItem*>(item);
        litem->projectionChanged();
    }
}

void MapGraphicsScene::addItem(GraphicsItem *item){
    QGraphicsScene::addItem(item);
    item->sceneChanged();
}