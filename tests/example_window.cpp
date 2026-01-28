#include <QApplication>
#include <QRandomGenerator>
#include <QTimer>

#include "GraphicsPolygon.h"
#include "GraphicsPixmap.h"
#include "MapGraphicsView.h"

#include "SimpleProjection.h"
#include "SphericalMercator.h"
#include "Mercator.h"

#include "simple_dataset.hpp"

QColor randomColor(){
    return QColor(
        QRandomGenerator::global()->bounded(255),
        QRandomGenerator::global()->bounded(255),
        QRandomGenerator::global()->bounded(255)
    );
}

// returns pixmap and anchor
QPair<QPixmap,QPointF> triangleMarker(){
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

// returns pixmap and anchor
QPair<QPixmap,QPointF> circleMarker(){
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

int main(int argc, char *argv[]){
    QApplication app(argc,argv);

    MapGraphicsView *view = new MapGraphicsView(new MapGraphicsScene(new SphericalMercator));

    GraphicsPolygon *water = new GraphicsPolygon(waterPoly);
    water->setBrush(Qt::blue);
    water->setZValue(-1);
    water->addTo(view);
    
    GraphicsPolygon *eurasia = new GraphicsPolygon(eurasiaPoly);
    GraphicsPolygon *africa = new GraphicsPolygon(africaPoly);
    GraphicsPolygon *northAmerica = new GraphicsPolygon(northAmericaPoly);
    GraphicsPolygon *southAmerica = new GraphicsPolygon(southAmericaPoly);
    GraphicsPolygon *australia = new GraphicsPolygon(australiaPoly);
    GraphicsPolygon *greenland = new GraphicsPolygon(greenlandPoly);
    GraphicsPolygon *antarctica = new GraphicsPolygon(antarcticaPoly);

    auto marker = triangleMarker();
    GraphicsPixmap *saintP = new GraphicsPixmap(marker.first);
    saintP->setGPos(saintPpos);
    saintP->setAnchor(marker.second);

    eurasia->setBrush(randomColor());
    africa->setBrush(randomColor());
    northAmerica->setBrush(randomColor());
    southAmerica->setBrush(randomColor());
    australia->setBrush(randomColor());
    greenland->setBrush(randomColor());
    antarctica->setBrush(randomColor());

    eurasia->addTo(view);
    africa->addTo(view);
    northAmerica->addTo(view);
    southAmerica->addTo(view);
    australia->addTo(view);
    greenland->addTo(view);
    antarctica->addTo(view);
    saintP->addTo(view);
    
    QTimer::singleShot(3000,[view](){
        view->setProjection(new SimpleProjection);
        qDebug() << "Projection switched!";
    });

    view->show();

    return app.exec();
}