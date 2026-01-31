#pragma once

#include "GraphicsItem.h"
#include "TypedGraphicsGroup.hpp"

#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QBitmap>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class IGraphicsPixmap{
    public:
        IGraphicsPixmap(const QPixmap &pixmap = QPixmap());
        virtual void setPixmap(const QPixmap &pixmap);
        QPixmap pixmap() const;

        virtual void setOffset(const QPointF &offset);
        QPointF offset() const;

        // anchor is negative offset
        virtual void setAnchor(const QPointF &anchor);
        QPointF anchor();
    private:
        QPixmap _pixmap;
        QPointF _offset;
};

class GraphicsPixmap : public GraphicsItem, public IGraphicsPixmap {
    public:
        enum { Type = BaseType + 5 };
        explicit GraphicsPixmap(GraphicsItem *parent = nullptr);
        explicit GraphicsPixmap(const QPixmap &pixmap, GraphicsItem *parent = nullptr);

        void setPixmap(const QPixmap &pixmap) override;
        void setOffset(const QPointF &offset) override;

        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
        QPainterPath shape() const override;
        bool contains(const QPointF &point) const override;

        int type() const override;
};

class GraphicsMultiPixmap: public TypedGraphicsGroup<GraphicsPixmap>, public IGraphicsPixmap {
    public:
        enum { Type = GroupTypeOffset + GraphicsPixmap::Type };
        GraphicsMultiPixmap(GraphicsItem *parent = nullptr);
        GraphicsMultiPixmap(const QPixmap &pixmap, const MultiPoint &points = {}, GraphicsItem *parent = nullptr);

        void setPixmap(const QPixmap &pixmap) override;
        void setOffset(const QPointF &offset) override;
        void setAnchor(const QPointF &anchor) override;

        void setPoints(const MultiPoint &points);
        MultiPoint points() const;

        int type() const override;
};