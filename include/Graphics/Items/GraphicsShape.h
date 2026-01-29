#pragma once

#include <QPen>
#include <QBrush>

class IGraphicsLine{
    public:
        IGraphicsLine();
        virtual void setPen(const QPen &pen);
        virtual QPen pen() const;

    private:
        QPen _pen;
};

class IGraphicsShape{
    public:
        virtual void setBrush(const QBrush &brush);
        virtual QBrush brush() const;
    private:
        QBrush _brush;
};