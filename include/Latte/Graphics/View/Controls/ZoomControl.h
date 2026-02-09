#pragma once

#include "Latte/Graphics/View/Controls/MapViewControl.h"

class ZoomControl: public MapViewControl{
    public:
        using MapViewControl::MapViewControl;

        void setFactor(double zoomFactor);
        double getFactor() const;

    protected:
        bool onViewEvent(QEvent *event) override;
        bool onViewportEvent(QEvent *event) override;

    private:
        bool handleWheel(QEvent *event);

    private:
        double _factor = 0.25;
};