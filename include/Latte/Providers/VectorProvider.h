#pragma once

#include "Latte/Graphics/Items/GraphicsItem.h"


class VectorProvider{
    public:
        struct IStyler{
            virtual void applyStyle(GraphicsItem *item,const QVariant &data) = 0;
        };

    public:
        VectorProvider();

        virtual void onNewLayer(GraphicsItem *item,const QVariant &data);
        
        void setStyler(IStyler *styler);
        IStyler *styler() const;

    private:
        std::unique_ptr<IStyler> _styler = nullptr;
};

class RandomVectorStyler : public VectorProvider::IStyler{
    public:
        void applyStyle(GraphicsItem *item,const QVariant &data) override;

        static QColor randomColor();
        // returns pixmap and anchor
        static QPair<QPixmap,QPointF> circleMarker();
        static QPair<QPixmap,QPointF> triangleMarker();
        // returns pen with randomized color
        static QPen randomizedPen(QPen pen);
        // returns brush with randomized color
        static QBrush randomizedBrush(QBrush brush);
};