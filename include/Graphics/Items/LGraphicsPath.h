#pragma once

#include "LGraphicsShape.h"
#include <QPainter>
#include <QPainterPath>

class LGraphicsPath : public LGraphicsShape {
    public:
        LGraphicsPath(LGraphicsItem *parent = nullptr);

        virtual QPainterPath path(const IProjection *proj) const = 0;

        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
        QPainterPath shape() const override;

    protected:
        bool contains(const QPointF &point) const override;
        QPainterPath projectedPath() const;
};