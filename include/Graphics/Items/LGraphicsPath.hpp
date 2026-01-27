#pragma once

#include "LGraphicsShape.hpp"
#include <QPainter>
#include <QPainterPath>

class LGraphicsPath : public LGraphicsShape {
    public:
        LGraphicsPath(LGraphicsItem *parent = nullptr): LGraphicsShape(parent){

        }

        virtual QPainterPath path(const IProjection *proj) const = 0;

        QRectF boundingRect() const override{
            return projectedPath().boundingRect()
                    .adjusted(-pen().widthF()/2, -pen().widthF()/2,
                                pen().widthF()/2, pen().widthF()/2);
        }

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
            Q_UNUSED(option)
            Q_UNUSED(widget)
        
            painter->setPen(pen());
            painter->setBrush(brush());
            painter->drawPath(projectedPath());
        }

        QPainterPath shape() const override {
            QPainterPathStroker stroker;
            stroker.setWidth(pen().widthF());
            stroker.setCapStyle(pen().capStyle());
            stroker.setJoinStyle(pen().joinStyle());
            return stroker.createStroke(projectedPath());
        }

    protected:
        bool contains(const QPointF &point) const override{
            return projectedPath().contains(point);
        }

        virtual void sceneChanged() override{
            updatePathCache();
        }

        void updatePathCache(){
            if(projection())
                projectedPathCache = path(projection());
        }

        QPainterPath projectedPath() const {
            return projectedPathCache;
        }

    private:
        QPainterPath projectedPathCache;
};