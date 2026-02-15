#pragma once

#include "Latte/Projection/IProjection.hpp"
#include "Latte/Projection/SimpleProjection.h"
#include "Latte/Projection/Mercator.h"
#include "Latte/Projection/SphericalMercator.h"
#include "Latte/Graphics/View/MapGraphicsView.h"

#include <QComboBox>

class ProjectionsFabric{
    public:
        template<typename Proj>
        void regProjection(QString projName){
            factoryMap[projName] = [](){ return new Proj(); };
        }

        IProjection *get(QString projName) const{
            return factoryMap[projName]();
        }

        QStringList projections() const {
            return factoryMap.keys();
        }

    private:
        QMap<QString,std::function<IProjection*()>> factoryMap;
};

class ProjComboBox: public QComboBox{
    public:
        ProjComboBox(MapGraphicsView *view) : QComboBox(view), view(view) {
            projFabric.regProjection<SimpleProjection>("Simple projection");
            projFabric.regProjection<Mercator>("Mercator");
            projFabric.regProjection<SphericalMercator>("Spherical mercator");

            QComboBox::addItems(projFabric.projections());
            QComboBox::setCurrentText("Simple projection");

            connect(this,&QComboBox::currentTextChanged,[this](QString projName){
                if(this->view) 
                    this->view->setProjection(projFabric.get(projName));
            });

        }

        void setView(MapGraphicsView *view){
            this->view = view;
        }

    private:
        ProjectionsFabric projFabric;
        MapGraphicsView *view;
};