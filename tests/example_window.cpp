#include <QApplication>
#include <QRandomGenerator>
#include <QTimer>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMap>

#include "Latte/Graphics/Items/GraphicsLineString.h"
#include "Latte/Graphics/Items/GraphicsPolygon.h"
#include "Latte/Graphics/Items/GraphicsPixmap.h"
#include "Latte/Graphics/Items/GraphicsGroup.h"
#include "Latte/Graphics/View/MapGraphicsView.h"
#include "Latte/Providers/VectorProvider.h"

#include "simple_dataset.hpp"
#include "ProjComboBox.hpp"


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

    auto marker = RandomVectorStyler::triangleMarker();
    GraphicsPixmap *saintP = new GraphicsPixmap(marker.first);
    saintP->setGPos(saintPpos);
    saintP->setAnchor(marker.second);

    eurasia->setBrush(RandomVectorStyler::randomColor());
    africa->setBrush(RandomVectorStyler::randomColor());
    northAmerica->setBrush(RandomVectorStyler::randomColor());
    southAmerica->setBrush(RandomVectorStyler::randomColor());
    australia->setBrush(RandomVectorStyler::randomColor());
    greenland->setBrush(RandomVectorStyler::randomColor());
    antarctica->setBrush(RandomVectorStyler::randomColor());

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
    marker = RandomVectorStyler::circleMarker();
    GraphicsPixmap *point = new GraphicsPixmap(marker.first);
    point->setGPos(pointTest);
    point->setAnchor(marker.second);

    GraphicsLineString *line = new GraphicsLineString(lineTest);
    line->setPen(RandomVectorStyler::randomizedPen(line->pen()));

    GraphicsPolygon *poly = new GraphicsPolygon(polyTest);
    poly->setPen(RandomVectorStyler::randomizedPen(poly->pen()));
    poly->setBrush(RandomVectorStyler::randomizedBrush(poly->brush()));

    marker = RandomVectorStyler::circleMarker();
    GraphicsMultiPixmap *multiPoint = new GraphicsMultiPixmap(marker.first,mutliPointTest);
    multiPoint->setAnchor(marker.second);

    GraphicsMultiLineString *multiLine = new GraphicsMultiLineString(multiLineTest);
    multiLine->setPen(RandomVectorStyler::randomizedPen(multiLine->pen()));

    GraphicsMultiPolygon *multiPoly = new GraphicsMultiPolygon(multiPolyTest);
    multiPoly->setPen(RandomVectorStyler::randomizedPen(multiPoly->pen()));
    multiPoly->setBrush(RandomVectorStyler::randomizedBrush(multiPoly->brush()));

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