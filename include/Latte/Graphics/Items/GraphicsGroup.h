#pragma once

#include "Latte/Graphics/Items/GraphicsItem.h"

class GraphicsGroup : public GraphicsItem {
    public:
        GraphicsGroup(GraphicsItem* parent = nullptr);
        GraphicsGroup(QVector<GraphicsItem*> items, GraphicsItem* parent = nullptr);

        void add(GraphicsItem *item);
        void add(QVector<GraphicsItem*> items);
        void remove(GraphicsItem *item, bool removeFromScene = true);
        void remove(QVector<GraphicsItem*> items, bool removeFromScene = true);

        QList<GraphicsItem*> items() const;

        QRectF boundingRect() const override;
        QPainterPath shape() const override;

        void sceneChanged() override;
        void projectionChanged() override;

        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

        bool isObscuredBy(const QGraphicsItem* item) const override;

        QPainterPath opaqueArea() const override;
};