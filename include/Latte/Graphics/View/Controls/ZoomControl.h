#pragma once

#include "Latte/Graphics/View/Controls/MapViewControl.h"

#include <QGraphicsView>

class ZoomControl: public MapViewControl{
    public:
        enum ZoomType{
            CENTER = QGraphicsView::AnchorViewCenter,
            CURSOR = QGraphicsView::AnchorUnderMouse
        };

        using MapViewControl::MapViewControl;

        void setFactor(double zoomFactor);
        double getFactor() const;

        void setType(ZoomType type);
        ZoomType getType() const;

    protected:
        bool onViewEvent(QEvent *event) override;
        bool onViewportEvent(QEvent *event) override;

    private:
        bool handleWheel(QEvent *event);

    private:
        double _factor = 0.25;
        ZoomType _type = ZoomType::CURSOR;
};