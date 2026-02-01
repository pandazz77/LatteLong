#pragma once

#include "GraphicsItem.h"
#include "GraphicsShape.h"
#include <QPainter>
#include <QPainterPath>

class GraphicsPath : public GraphicsItem, public IGraphicsLine {
    public:
        GraphicsPath(GraphicsItem *parent = nullptr);

        virtual QPainterPath path(const IProjection *proj) const = 0;

        QRectF boundingRect() const override;
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
        QPainterPath shape() const override;

    protected:
        bool contains(const QPointF &point) const override;
        QPainterPath projectedPath() const;
        void updatePathCache();

        virtual void sceneChanged() override;
        virtual void projectionChanged() override;

    private:
        QPainterPath _projectedPathCache;
};