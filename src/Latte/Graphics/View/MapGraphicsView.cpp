#include "Latte/Graphics/View/MapGraphicsView.h"

#include "Latte/Projection/GeometryConvertor.h"
#include "Latte/Projection/SimpleProjection.h"

#include "Latte/Graphics/View/Controls/ZoomControl.h"

/**
 * @brief Standard MapGraphicsView controls fabric
 * 
 * @param view View, that controls are creating for
 * @return QVector<MapViewControl*> list of fabricated controls
 */
QVector<MapViewControl*> _createStdControls(MapGraphicsView *view){
    return {
        new ZoomControl(view)
    };
}

MapGraphicsView::MapGraphicsView(MapGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent){
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(MapViewControl *stdcontrol: _createStdControls(this)){
        addControl(stdcontrol);
    }
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

void MapGraphicsView::showEvent(QShowEvent *event) {
    fitBounds();

    QGraphicsView::showEvent(event);
}

void MapGraphicsView::addControl(MapViewControl *control){
    if(control->view()) control->remove();
    control->assignView(this);
    installEventFilter(control);
    viewport()->installEventFilter(control);
    _controls.insert(control);
}

void MapGraphicsView::removeControl(MapViewControl *control){
    _controls.remove(control);
    control->assignView(nullptr);
    removeEventFilter(control);
    viewport()->removeEventFilter(control);
}

QSet<MapViewControl*> MapGraphicsView::controls() const{
    return _controls;
}
