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
    double zoomFactor = 0.25;
    double zoom = 1+sign*zoomFactor;
    
    view()->scale(zoom,zoom);
    return true;
}