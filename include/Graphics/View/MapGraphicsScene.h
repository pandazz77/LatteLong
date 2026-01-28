#pragma once

#include <QGraphicsScene>
#include "IProjection.hpp"

class LGraphicsItem;

class MapGraphicsScene: public QGraphicsScene{
    public:
        MapGraphicsScene(IProjection *proj, QObject *parent = nullptr);
        MapGraphicsScene(QObject *parent = nullptr);
        
        ~MapGraphicsScene();

        const IProjection *projection();
        void setProjection(IProjection *proj);

        void addItem(QGraphicsItem *item) = delete;
        void addItem(LGraphicsItem *item);

    private:
        IProjection *_proj = nullptr; // TODO: make unique
};