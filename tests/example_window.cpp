#include <QApplication>
#include <QRandomGenerator>
#include <QTimer>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMap>

#include "GraphicsPolygon.h"
#include "GraphicsPixmap.h"
#include "GraphicsGroup.h"
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

class ProjectionsFabric{
    public:
        template<typename Proj>
        void regProjection(QString projName){
            factoryMap[projName] = [](){ return new Proj(); };
        }

        IProjection *get(QString projName) const{
            return factoryMap[projName]();
        }

        QStringList projections() const {
            return factoryMap.keys();
        }

    private:
        QMap<QString,std::function<IProjection*()>> factoryMap;
};

int main(int argc, char *argv[]){
    QApplication app(argc,argv);
    QWidget *window = new QWidget;
    window->resize(800,600);
    window->setLayout(new QHBoxLayout(window));

    MapGraphicsView *view = new MapGraphicsView(new MapGraphicsScene(),window);
    window->layout()->addWidget(view);

    QComboBox *projectionsCombo = new QComboBox(window);
    ProjectionsFabric projFabric;
    projFabric.regProjection<SimpleProjection>("Simple projection");
    projFabric.regProjection<Mercator>("Mercator");
    projFabric.regProjection<SphericalMercator>("Spherical mercator");
    projectionsCombo->addItems(projFabric.projections());
    projectionsCombo->setCurrentText("Simple projection");
    projectionsCombo->connect(projectionsCombo,&QComboBox::currentTextChanged,[&](QString projName){
        view->setProjection(projFabric.get(projName));
    });
    window->layout()->addWidget(projectionsCombo);

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

    GraphicsGroup *america = new GraphicsGroup();
    america->add(northAmerica);
    america->add(southAmerica);
    america->addTo(view);

    america->remove(northAmerica); // WARNING: DOESNT WORK WELL

    window->show();

    return app.exec();
}