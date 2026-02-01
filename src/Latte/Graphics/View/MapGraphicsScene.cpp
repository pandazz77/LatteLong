#include "Latte/Graphics/View/MapGraphicsScene.h"

#include "Latte/Projection/SimpleProjection.h"
#include "Latte/Projection/GeometryConvertor.h"
#include "Latte/Graphics/Items/GraphicsItem.h"

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
    for(QGraphicsItem *item: items()){
        GraphicsItem *litem = dynamic_cast<GraphicsItem*>(item);
        litem->projectionChanged();
    }
}

void MapGraphicsScene::addItem(GraphicsItem *item){
    QGraphicsScene::addItem(item);
    item->sceneChanged();
}