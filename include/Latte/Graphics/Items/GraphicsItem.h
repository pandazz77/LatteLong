#pragma once

#include <QGraphicsItem>

#include "Latte/Projection/IProjection.hpp"
#include "Latte/Graphics/View/MapGraphicsScene.h"
#include "Latte/Graphics/View/MapGraphicsView.h"

class GraphicsItem : public QGraphicsItem{
    public:
        using QGraphicsItem::QGraphicsItem;

        MapGraphicsScene *scene() const;
        const IProjection *projection() const;
        const GeometryConvertor &convertor() const;

        void addTo(MapGraphicsScene *scene);
        void addTo(MapGraphicsView *view);

        virtual void sceneChanged();
        virtual void projectionChanged();

        void setGPos(const LatLng &geoPos); // set get position
        LatLng gPos() const; // get geo position

    protected:
        using QGraphicsItem::setPos;
        using QGraphicsItem::setX;
        using QGraphicsItem::setY;

        void updateScenePos();

    private:
        LatLng _geoPos;
};