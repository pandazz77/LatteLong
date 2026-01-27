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
            if(scene())
                return scene()->projection();
            return nullptr;
        }

        void addTo(MapGraphicsScene *scene) {
            scene->addItem(this);
        }

        void addTo(MapGraphicsView *view) {
            addTo(view->scene());
        }

    protected:
        virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value){
            if(QGraphicsItem::ItemSceneChange)
                sceneChanged();
            return QGraphicsItem::itemChange(change,value);
        }
        virtual void sceneChanged() = 0;
};