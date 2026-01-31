#include <QApplication>
#include <QRandomGenerator>
#include <QTimer>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMap>

#include "GraphicsLineString.h"
#include "GraphicsPolygon.h"
#include "GraphicsPixmap.h"
#include "GraphicsGroup.h"
#include "MapGraphicsView.h"

#include "simple_dataset.hpp"
#include "ProjComboBox.hpp"

QColor randomColor(){
    return QColor(
        QRandomGenerator::global()->bounded(255),
        QRandomGenerator::global()->bounded(255),
        QRandomGenerator::global()->bounded(255)
    );
}

QPen randomizedPen(QPen pen){
    pen.setColor(randomColor());
    return pen;
}

QBrush randomizedBrush(QBrush brush){
    brush.setColor(randomColor());
    return brush;
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
    QWidget *window = new QWidget;
    window->resize(800,600);
    window->setLayout(new QHBoxLayout(window));

    MapGraphicsView *view = new MapGraphicsView(new MapGraphicsScene(),window);
    window->layout()->addWidget(view);
    window->layout()->addWidget(new ProjComboBox(view));

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
    australia->addTo(view);
    greenland->addTo(view);
    antarctica->addTo(view);
    saintP->addTo(view);

    GraphicsGroup *america = new GraphicsGroup({northAmerica,southAmerica});
    // OR:
    // america->add(northAmerica);
    // america->add(southAmerica);
    america->addTo(view);

    // ==================== SAMPLE GEOMETRIES
    marker = circleMarker();
    GraphicsPixmap *point = new GraphicsPixmap(marker.first);
    point->setGPos(pointTest);
    point->setAnchor(marker.second);

    GraphicsLineString *line = new GraphicsLineString(lineTest);
    line->setPen(randomizedPen(line->pen()));

    GraphicsPolygon *poly = new GraphicsPolygon(polyTest);
    poly->setPen(randomizedPen(poly->pen()));
    poly->setBrush(randomizedBrush(poly->brush()));

    marker = circleMarker();
    GraphicsMultiPixmap *multiPoint = new GraphicsMultiPixmap(marker.first,mutliPointTest);
    multiPoint->setAnchor(marker.second);

    GraphicsMultiLineString *multiLine = new GraphicsMultiLineString(multiLineTest);
    multiLine->setPen(randomizedPen(multiLine->pen()));

    GraphicsMultiPolygon *multiPoly = new GraphicsMultiPolygon(multiPolyTest);
    multiPoly->setPen(randomizedPen(multiPoly->pen()));
    multiPoly->setBrush(randomizedBrush(multiPoly->brush()));

    point->addTo(view);
    line->addTo(view);
    poly->addTo(view);
    multiPoint->addTo(view);
    multiLine->addTo(view);
    multiPoly->addTo(view);

    // ====================

    window->show();

    return app.exec();
}