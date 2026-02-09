#pragma once

#include <QGraphicsView>
#include "Latte/Graphics/View/MapGraphicsScene.h"
#include "Latte/Graphics/View/Controls/MapViewControl.h"

class MapGraphicsView: public QGraphicsView{
    public:
        MapGraphicsView(MapGraphicsScene *scene, QWidget *parent = nullptr);
        MapGraphicsView(QWidget *parent = nullptr);

        MapGraphicsScene *scene() const;

        void setProjection(IProjection *rawProjPtr);

        const IProjection *projection() const;
        const GeometryConvertor &convertor() const;

        void addControl(MapViewControl *control);
        void removeControl(MapViewControl *control);
        QVector<MapViewControl*> controls() const;

        void fitBounds();

    protected:
        void showEvent(QShowEvent *event) override;

    private:
        QVector<MapViewControl*> _controls;
};