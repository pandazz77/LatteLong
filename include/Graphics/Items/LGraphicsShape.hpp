#include "LGraphicsItem.hpp"
#include <QPen>
#include <QBrush>

class LGraphicsShape : public LGraphicsItem
{
public:
    LGraphicsShape(LGraphicsItem *parent = nullptr) : LGraphicsItem(parent), _pen(Qt::black), _brush(Qt::NoBrush){
        _pen.setCosmetic(true);
    }

    void setPen(const QPen &pen){
        _pen = pen;
    }

    void setBrush(const QBrush &brush){
        _brush = brush;
    }

    QPen pen() const {
        return _pen;
    }

    QBrush brush() const {
        return _brush;
    }

protected:
    LGraphicsShape(QAbstractGraphicsShapeItemPrivate &dd, LGraphicsItem *parent = nullptr);

private:
    QPen _pen;
    QBrush _brush;
};