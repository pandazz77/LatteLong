#pragma once

#include "LGraphicsItem.h"

#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QBitmap>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class LGraphicsPixmap : public LGraphicsItem {
    public:

        explicit LGraphicsPixmap(LGraphicsItem *parent = nullptr);
        explicit LGraphicsPixmap(const QPixmap &pixmap, LGraphicsItem *parent = nullptr);

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