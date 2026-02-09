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
        QSet<MapViewControl*> controls() const;
        
        template<typename TControl>
        TControl getControlByType(){
            for(MapViewControl *control: _controls){
                if(TControl result = dynamic_cast<TControl>(control))
                    return result;
            }
            return nullptr;
        }

        void fitBounds();

    protected:
        void showEvent(QShowEvent *event) override;

    private:
        QSet<MapViewControl*> _controls;
};