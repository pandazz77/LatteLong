#pragma once

#include <QGraphicsScene>
#include "IProjection.hpp"
#include "SimpleProjection.hpp"
#include "GeometryConvertor.h"

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