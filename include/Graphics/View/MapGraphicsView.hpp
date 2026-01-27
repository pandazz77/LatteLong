#pragma once

#include <QGraphicsView>
#include <QWheelEvent>
#include "MapGraphicsScene.hpp"
#include "GeometryConvertor.h"


class MapGraphicsView: public QGraphicsView{
    public:
        MapGraphicsView(MapGraphicsScene *scene, QWidget *parent = nullptr) : QGraphicsView(scene,parent){
            scale(1,-1); // rotate Y axis

            setDragMode(QGraphicsView::ScrollHandDrag);
            fitBounds();
        }

        MapGraphicsView(QWidget *parent = nullptr) : MapGraphicsView(new MapGraphicsScene(new SimpleProjection,nullptr), parent) { // wtf. TODO: deal with construction args

        }

        // QGraphicsScene *scene() const = delete;
        MapGraphicsScene *scene() const {
            return dynamic_cast<MapGraphicsScene*>(QGraphicsView::scene());
        }

        void setProjection(IProjection *proj){
            scene()->setProjection(proj);
            fitBounds();
        }

        const IProjection *projection(){
            return scene()->projection();
        }

        void fitBounds(){
            fitInView(GeometryConvertor::bounds(projection()->bounds(),projection()));
        }

    protected:
        void wheelEvent(QWheelEvent *event) override {
            int sign = event->angleDelta().y() < 0 ? -1 : 1;
            double zoomFactor = 0.25;
            double zoom = 1+sign*zoomFactor;
            
            scale(zoom,zoom);
        }

    private:
        double minZoom = -999;
        double maxZoom = 999;
        double currentZoom = 1;
};