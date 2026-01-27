#pragma once

#include <QGraphicsScene>
#include "IProjection.hpp"

class MapGraphicsScene: public QGraphicsScene{
    public:
        MapGraphicsScene(IProjection *proj, QObject *parent = nullptr);
        MapGraphicsScene(QObject *parent = nullptr);
        
        ~MapGraphicsScene();

        const IProjection *projection();
        void setProjection(IProjection *proj);

    private:
        IProjection *_proj = nullptr; // TODO: make unique
};