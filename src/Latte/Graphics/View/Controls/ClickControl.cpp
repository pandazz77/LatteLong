#include "Latte/Graphics/View/Controls/ClickControl.h"

#include "Latte/Graphics/View/MapGraphicsView.h"

#include <QMouseEvent>

bool ClickControl::onViewportEvent(QEvent *event){
    bool isPress = event->type() == QEvent::MouseButtonPress;
    bool isRelease = event->type() == QEvent::MouseButtonRelease;
    bool isMoving = event->type() == QEvent::MouseMove;

    // drop click event if it is drag
    if(isMoving){
        pressPos = QPointF();
        return false;
    }

    if(isPress || isRelease){
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);

        QPoint remapped = view()->mapFromParent(mouseEvent->pos());

        if(!view()->rect().contains(remapped))
            return false;

        QPointF pos = view()->mapToScene(remapped);
        
        if(isPress) 
            pressPos = pos;
        else {
            if(pos == pressPos) 
                return handleClick(pos);
        }
    }
    return false;
}
