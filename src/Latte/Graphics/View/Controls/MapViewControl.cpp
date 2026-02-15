#include "Latte/Graphics/View/Controls/MapViewControl.h"

#include "Latte/Graphics/View/MapGraphicsView.h"


MapViewControl::MapViewControl(QObject *parent) : QObject(parent){

}

void MapViewControl::setView(MapGraphicsView *view){
    view->addControl(this);
}

void MapViewControl::remove(){
    this->_view->removeControl(this);
}

MapGraphicsView *MapViewControl::view(){
    return this->_view;
}

bool MapViewControl::onViewEvent(QEvent *event){
    return false;
}

bool MapViewControl::onViewportEvent(QEvent *event){
    return false;
}


bool MapViewControl::eventFilter(QObject *obj, QEvent *event){
    if(MapGraphicsView *view = dynamic_cast<MapGraphicsView*>(obj)){
        return onViewEvent(event);
    } else if(QWidget *viewport = dynamic_cast<QWidget*>(obj)){
        return onViewportEvent(event);
    }
    return false;
}

void MapViewControl::assignView(MapGraphicsView *view){
    this->_view = view;
}