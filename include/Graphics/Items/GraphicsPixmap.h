#pragma once

#include "GraphicsItem.h"

#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QBitmap>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class GraphicsPixmap : public GraphicsItem {
    public:

        explicit GraphicsPixmap(GraphicsItem *parent = nullptr);
        explicit GraphicsPixmap(const QPixmap &pixmap, GraphicsItem *parent = nullptr);

        void setPixmap(const QPixmap &pixmap);
        QPixmap pixmap() const;

        void setOffset(const QPointF &offset);
        QPointF offset() const;

        // anchor is negative offset
        void setAnchor(const QPointF &anchor);
        QPointF anchor();

        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
        QPainterPath shape() const override;
        bool contains(const QPointF &point) const override;

    private:
        QPixmap _pixmap;
        QPointF _offset;
};