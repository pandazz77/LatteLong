#include "Latte/Graphics/View/Controls/ZoomControl.h"

#include "Latte/Graphics/View/MapGraphicsView.h"

#include <QWheelEvent>

bool ZoomControl::onViewportEvent(QEvent *event) {
    if(event->type() == QEvent::Wheel)
        return handleWheel(event);
    return false;
}

bool ZoomControl::onViewEvent(QEvent *event){
    if(event->type() == QEvent::Wheel)
        return handleWheel(event);
    return false;
}

bool ZoomControl::handleWheel(QEvent *event){
    QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);

    int sign = wheelEvent->angleDelta().y() < 0 ? -1 : 1;
    double zoom = 1+sign*_factor;

    // idk why transformation anchor ingores for the first time
    if((int)view()->transformationAnchor()!=(int)_type){
        view()->setTransformationAnchor((QGraphicsView::ViewportAnchor)_type);
    }
    
    view()->scale(zoom,zoom);
    return true;
}

void ZoomControl::setFactor(double zoomFactor){
    _factor = zoomFactor;
}

double ZoomControl::getFactor() const{
    return _factor;
}


void ZoomControl::setType(ZoomType type){
    _type = type;
}

ZoomControl::ZoomType ZoomControl::getType() const{
    return _type;
}
