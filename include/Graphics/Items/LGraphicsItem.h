#pragma once

#include <QGraphicsItem>

#include "IProjection.hpp"
#include "MapGraphicsScene.hpp"
#include "MapGraphicsView.hpp"

class LGraphicsItem : public QGraphicsItem{
    public:
        using QGraphicsItem::QGraphicsItem;

        MapGraphicsScene *scene() const;

        const IProjection *projection() const;

        void addTo(MapGraphicsScene *scene);
        void addTo(MapGraphicsView *view);
};