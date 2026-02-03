#pragma once

#include <QGraphicsItem>

#include "IProjection.hpp"
#include "MapGraphicsScene.h"
#include "MapGraphicsView.h"

class GraphicsItem : public QGraphicsItem{
    public:
        enum {
            BaseType = UserType + 1,
            Type = BaseType,
        };

        using QGraphicsItem::QGraphicsItem;

        MapGraphicsScene *scene() const;
        const IProjection *projection() const;

        void addTo(MapGraphicsScene *scene);
        void addTo(MapGraphicsView *view);

        virtual void sceneChanged();
        virtual void projectionChanged();

        void setGPos(const LatLng &geoPos); // set get position
        LatLng gPos() const; // get geo position

        int type() const override;

        template <typename T> 
        static T cast(GraphicsItem *item){
            return qgraphicsitem_cast<T>(item);
        };

        template <typename T>
        T cast(){
            return cast<T>(this);
        }

    protected:
        using QGraphicsItem::setPos;
        using QGraphicsItem::setX;
        using QGraphicsItem::setY;

        void updateScenePos();

    private:
        LatLng _geoPos;
};