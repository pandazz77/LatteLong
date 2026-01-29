#pragma once

#include "GraphicsItem.h"

class GraphicsGroup : public GraphicsItem {
    public:
        GraphicsGroup(GraphicsItem* parent = nullptr);

        void add(GraphicsItem *item);
        void remove(GraphicsItem *item);

        QList<GraphicsItem*> items() const;

        QRectF boundingRect() const override;
        QPainterPath shape() const override;

        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

        bool isObscuredBy(const QGraphicsItem* item) const override;

        QPainterPath opaqueArea() const override;
};