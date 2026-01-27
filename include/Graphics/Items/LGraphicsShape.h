#include "LGraphicsItem.h"
#include <QPen>
#include <QBrush>

class LGraphicsShape : public LGraphicsItem {
    public:
        LGraphicsShape(LGraphicsItem *parent = nullptr);

        void setPen(const QPen &pen);
        void setBrush(const QBrush &brush);

        QPen pen() const;
        QBrush brush() const;

    protected:
        LGraphicsShape(QAbstractGraphicsShapeItemPrivate &dd, LGraphicsItem *parent = nullptr);

    private:
        QPen _pen;
        QBrush _brush;
};