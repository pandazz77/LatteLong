#pragma once

#include <QGraphicsView>
#include <QWheelEvent>
#include "MapGraphicsScene.h"


class MapGraphicsView: public QGraphicsView{
    public:
        MapGraphicsView(MapGraphicsScene *scene, QWidget *parent = nullptr);
        MapGraphicsView(QWidget *parent = nullptr);

        // QGraphicsScene *scene() const = delete;
        MapGraphicsScene *scene() const;

        void setProjection(IProjection *proj);

        const IProjection *projection();

        void fitBounds();

    protected:
        void wheelEvent(QWheelEvent *event) override;
};