#pragma once


#include "Latte/Graphics/View/Controls/MapViewControl.h"

#include <QPointF>

/**
 * @brief Abstract ClickControl class
 * 
 */
class ClickControl: public MapViewControl{
    public:
        using MapViewControl::MapViewControl;

    protected:
        virtual bool handleClick(const QPointF &scenePos) = 0;

        virtual bool onViewportEvent(QEvent *event) override;

    private:
        QPointF pressPos;
};