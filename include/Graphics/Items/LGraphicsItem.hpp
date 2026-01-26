#pragma once

#include <QGraphicsItem>
#include <IProjection.hpp>
#include "MapGraphicsScene.hpp"
#include "MapGraphicsView.hpp"

class LGraphicsItem : public QGraphicsItem{
    public:
        using QGraphicsItem::QGraphicsItem;

        MapGraphicsScene *scene() const {
            return dynamic_cast<MapGraphicsScene*>(QGraphicsItem::scene());
        }

        const IProjection *projection() const {
            return scene()->projection();
        }

        void addTo(MapGraphicsScene *scene) {
            scene->addItem(this);
        }

        void addTo(MapGraphicsView *view) {
            addTo(view->scene());
        }
};