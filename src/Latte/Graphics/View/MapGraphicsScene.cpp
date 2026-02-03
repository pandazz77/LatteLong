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
    return _convertor.projection();
}

void MapGraphicsScene::setProjection(IProjection *proj){
    _convertor.setProjection(proj);
    update();
    setSceneRect(_convertor.bounds(projection()->bounds()));
    for(QGraphicsItem *item: items()){
        GraphicsItem *litem = dynamic_cast<GraphicsItem*>(item);
        litem->projectionChanged();
    }
}

void MapGraphicsScene::addItem(GraphicsItem *item){
    QGraphicsScene::addItem(item);
    item->sceneChanged();
}