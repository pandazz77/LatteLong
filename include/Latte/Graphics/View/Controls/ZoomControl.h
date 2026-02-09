#pragma once

#include "Latte/Graphics/View/Controls/MapViewControl.h"

class ZoomControl: public MapViewControl{
    public:
        using MapViewControl::MapViewControl;
    protected:
        bool onViewEvent(QEvent *event) override;
        bool onViewportEvent(QEvent *event) override;

    private:
        bool handleWheel(QEvent *event);
};