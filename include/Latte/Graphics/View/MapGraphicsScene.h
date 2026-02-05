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

        void addItem(GraphicsItem *item);

    protected:
        using QGraphicsScene::addItem;
        using QGraphicsScene::addEllipse;
        using QGraphicsScene::addLine;
        using QGraphicsScene::addPath;
        using QGraphicsScene::addPixmap;
        using QGraphicsScene::addPolygon;
        using QGraphicsScene::addRect;
        using QGraphicsScene::addSimpleText;
        using QGraphicsScene::addWidget;
        using QGraphicsScene::createItemGroup;
        using QGraphicsScene::destroyItemGroup;

    private:
        GeometryConvertor _convertor;
};