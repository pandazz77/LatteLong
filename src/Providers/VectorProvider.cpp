#include "VectorProvider.h"

#include "GraphicsShape.h"
#include "GraphicsPixmap.h"

#include <QRandomGenerator>

VectorProvider::VectorProvider(){
    setStyler(new RandomVectorStyler);
}

void VectorProvider::onNewLayer(GraphicsItem *item,const QVariant &data){
    if(_styler)
        _styler->applyStyle(item,data);
}
        
void VectorProvider::setStyler(IStyler *styler){
    _styler.reset(styler);
}

VectorProvider::IStyler *VectorProvider::styler() const{
    return _styler.get();
}

// ==================================

void RandomVectorStyler::applyStyle(GraphicsItem *item,const QVariant &data){
    if(dynamic_cast<IGraphicsPixmap*>(item)){
        IGraphicsPixmap *pixmap = dynamic_cast<IGraphicsPixmap*>(item);
        auto marker = circleMarker();
        pixmap->setPixmap(marker.first);
        pixmap->setAnchor(marker.second);

    } 
    else if(dynamic_cast<IGraphicsLine*>(item)){
        IGraphicsLine *line = dynamic_cast<IGraphicsLine*>(item);
        line->setPen(randomizedPen(line->pen()));

    }
    // NOT ELSE IF!
    if(dynamic_cast<IGraphicsShape*>(item)){
        IGraphicsShape *shape = dynamic_cast<IGraphicsShape*>(item);
        shape->setBrush(randomizedBrush(shape->brush()));

    }
}

QColor RandomVectorStyler::randomColor(){
    return QColor(
        QRandomGenerator::global()->bounded(255),
        QRandomGenerator::global()->bounded(255),
        QRandomGenerator::global()->bounded(255)
    );
}

// returns pixmap and anchor
QPair<QPixmap,QPointF> RandomVectorStyler::circleMarker(){
    QPixmap pixmap(12,12);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    QPen pen(randomColor(),1);
    QBrush brush(randomColor());

    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawEllipse(pixmap.rect());

    return {
        pixmap,
        {pixmap.height()/2.0,pixmap.width()/2.0}
    };
}

QPair<QPixmap,QPointF> RandomVectorStyler::triangleMarker(){
    constexpr int SIZE = 20;
    QPixmap pixmap(SIZE,SIZE);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    QPen pen(randomColor(),1);
    QBrush brush(randomColor());

    painter.setPen(pen);
    painter.setBrush(brush);
    QRect rect = pixmap.rect();
    QPoint anchor{SIZE/2,SIZE};
    QPolygon triangle{
        rect.topLeft(),
        rect.topRight(),
        anchor
    };
    painter.drawPolygon(triangle);

    return {
        pixmap,
        anchor
    };
}

// returns pen with randomized color
QPen RandomVectorStyler::randomizedPen(QPen pen){
    pen.setColor(randomColor());
    return pen;
}

// returns brush with randomized color
QBrush RandomVectorStyler::randomizedBrush(QBrush brush){
    brush.setColor(randomColor());
    return brush;
}
