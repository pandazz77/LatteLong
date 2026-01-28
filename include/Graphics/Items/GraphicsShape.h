#include "GraphicsItem.h"
#include <QPen>
#include <QBrush>

class GraphicsShape : public GraphicsItem {
    public:
        GraphicsShape(GraphicsItem *parent = nullptr);

        void setPen(const QPen &pen);
        void setBrush(const QBrush &brush);

        QPen pen() const;
        QBrush brush() const;

    protected:
        GraphicsShape(QAbstractGraphicsShapeItemPrivate &dd, GraphicsItem *parent = nullptr);

    private:
        QPen _pen;
        QBrush _brush;
};