#pragma once

#include <QGraphicsItem>

#include "IProjection.hpp"
#include "MapGraphicsScene.h"
#include "MapGraphicsView.h"

class LGraphicsItem : public QGraphicsItem{
    public:
        using QGraphicsItem::QGraphicsItem;

        MapGraphicsScene *scene() const;

        const IProjection *projection() const;

        void addTo(MapGraphicsScene *scene);
        void addTo(MapGraphicsView *view);

        void setPos(const QPointF &pos) = delete;
        void setPos(qreal x, qreal y) = delete;

        QPointF pos() const = delete;
        QPointF scenePos() const = delete;
};