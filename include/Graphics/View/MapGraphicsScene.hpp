#pragma once

#include <QGraphicsScene>
#include "IProjection.hpp"
#include "SimpleProjection.hpp"

class MapGraphicsScene: public QGraphicsScene{
    public:
        MapGraphicsScene(IProjection *proj, QObject *parent=nullptr) : QGraphicsScene(parent), _proj(proj) {
            
        }

        MapGraphicsScene(QObject *parent = nullptr) : MapGraphicsScene(new SimpleProjection,parent) {

        }
        
        ~MapGraphicsScene() {
        
        }

        const IProjection *projection(){
            return _proj;
        }

        void setProjection(IProjection *proj){
            if(_proj)
                delete _proj;
            _proj = proj;
        }

    private:
        IProjection *_proj = nullptr; // TODO: make unique
};