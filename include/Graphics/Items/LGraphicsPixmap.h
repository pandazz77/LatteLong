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

        void setGeoPos(const LatLng &pos);
        LatLng geoPos() const;

        void setOffset(const QPointF &offset);
        void setOffset(qreal x, qreal y);
        QPointF offset() const;

        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
        QPainterPath shape() const override;
        bool contains(const QPointF &point) const override;

    protected:
        virtual void sceneChanged() override;
        virtual void projectionChanged() override;

    private:
        QPointF projectedPos() const;
        void updateScenePos();

    private:
        QPixmap _pixmap;
        QPointF _offset;
        LatLng _pos;
};