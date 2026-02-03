#pragma once

#include <QGraphicsScene>
#include "Latte/Projection/GeometryConvertor.h"
#include "Latte/Projection/IProjection.hpp"

class GraphicsItem;

class MapGraphicsScene: public QGraphicsScene{
    public:
        MapGraphicsScene(IProjection *proj, QObject *parent = nullptr);
        MapGraphicsScene(QObject *parent = nullptr);
        
        ~MapGraphicsScene();

        const IProjection *projection();
        void setProjection(IProjection *rawProjPtr);
        const GeometryConvertor &convertor() const;

        void addItem(QGraphicsItem *item) = delete;
        void addItem(GraphicsItem *item);

    private:
        GeometryConvertor _convertor;
};