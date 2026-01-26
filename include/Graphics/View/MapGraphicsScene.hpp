#pragma once

#include <QGraphicsScene>
#include "IProjection.hpp"
#include "SimpleProjection.hpp"

class MapGraphicsScene: public QGraphicsScene{
    public:
        MapGraphicsScene(IProjection *proj, QObject *parent=nullptr) : QGraphicsScene(parent), proj(proj) {
            
        }

        MapGraphicsScene(QObject *parent = nullptr) : MapGraphicsScene(new SimpleProjection,parent) {

        }
        
        ~MapGraphicsScene() {
        
        }

        const IProjection *projection(){
            return proj;
        }

    private:
        IProjection *proj = nullptr;
};