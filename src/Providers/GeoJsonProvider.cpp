#include "GeoJsonProvider.h"

#include "GraphicsPixmap.h"
#include "GraphicsLineString.h"
#include "GraphicsPolygon.h"

#include <QFile>
#include <QRandomGenerator>

#define GJ_FEATURE "Feature"
#define GJ_FEATURECOLLECTION "FeatureCollection"
#define GJ_POINT "Point"
#define GJ_LINE "LineString"
#define GJ_POLY "Polygon"
#define GJ_MULTIPOINT "MultiPoint"
#define GJ_MULTILINE "MultiLineString"
#define GJ_MULTIPOLY "MultiPolygon"

QColor randomColor(){
    return QColor(
        QRandomGenerator::global()->bounded(255),
        QRandomGenerator::global()->bounded(255),
        QRandomGenerator::global()->bounded(255)
    );
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

QPen randomizedPen(QPen pen){
    pen.setColor(randomColor());
    return pen;
}

QBrush randomizedBrush(QBrush brush){
    brush.setColor(randomColor());
    return brush;
}


template<>
LatLng GeoJsonProvider::fetchGeometry<LatLng>(QVariantList lngLat){
    return LngLat(
        lngLat[0].toDouble(),
        lngLat[1].toDouble()
    );
}

template<>
LineString GeoJsonProvider::fetchGeometry<LineString>(QVariantList lngLatCoords){
    LineString result;
    for(auto var_pos: lngLatCoords.toList()){
        result.push_back(fetchGeometry<LatLng>(var_pos.toList()));
    }
    return result;
}

template<>
Polygon GeoJsonProvider::fetchGeometry<Polygon>(QVariantList lngLatPoly){
    LineString exterior(fetchGeometry<LineString>(lngLatPoly[0].toList()));
    MultiLineString interriors;
    if(lngLatPoly.size()>1){ 
        QVariantList var_interriors = lngLatPoly.sliced(1);
        interriors = fetchMultiGeometry<LineString>(var_interriors);
    }
    return Polygon(exterior,interriors);
}


template<class TGeometry>
MultiGeometry<TGeometry> GeoJsonProvider::fetchMultiGeometry(QVariantList multiItems){
    MultiGeometry<TGeometry> multi;
    for(auto var_item: multiItems){
        multi.push_back(fetchGeometry<TGeometry>(var_item.toList()));
    }
    return multi;
}


    
GraphicsGroup *GeoJsonProvider::load(const QJsonDocument &doc){
    return processFeatureCollection(doc.toVariant().toMap());
}

GraphicsGroup *GeoJsonProvider::fromFile(const QString &filePath){
    QFile file(filePath);
    bool opened = file.open(QIODevice::ReadOnly);
    assert(opened);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    return load(doc);
}


GraphicsItem *GeoJsonProvider::processSomeFeature(QVariantMap map){
    QString type = map["type"].toString();
    if(type == GJ_FEATURE) return processFeature(map);
    else if(type == GJ_FEATURECOLLECTION) return processFeatureCollection(map);
    qWarning() << "Undefined geojson type:" << type;
    return nullptr;
}

GraphicsItem *GeoJsonProvider::processFeature(QVariantMap map){
    assert(map["type"].toString() == GJ_FEATURE);

    GraphicsItem *item = createItemFromGeometry(map["geometry"].toMap());
    // HERE MUST BE PROPERTIES ASSIGMENT

    return item;
}

GraphicsGroup *GeoJsonProvider::processFeatureCollection(QVariantMap map){
    assert(map["type"].toString() == GJ_FEATURECOLLECTION);
    QVariantList var_features = map["features"].toList();
    GraphicsGroup *group = new GraphicsGroup;
    for(auto var_feature: var_features){
        group->add(processSomeFeature(var_feature.toMap()));
    }
    return group;
}

GraphicsItem *GeoJsonProvider::createItemFromGeometry(QVariantMap map){
    QString type = map["type"].toString();
    QVariantList coords = map["coordinates"].toList();


    if(type==GJ_POINT){
        auto marker = circleMarker();
        GraphicsPixmap *item = new GraphicsPixmap(marker.first);
        item->setAnchor(marker.second);
        item->setGPos(fetchGeometry<LatLng>(coords));
        return item;
    } else if(type==GJ_LINE){
        GraphicsLineString *item = new GraphicsLineString(fetchGeometry<LineString>(coords));
        item->setPen(randomizedPen(item->pen()));
        return item;
    } else if(type==GJ_POLY){
        GraphicsPolygon *item = new GraphicsPolygon(fetchGeometry<Polygon>(coords));
        item->setPen(randomizedPen(item->pen()));
        item->setBrush(randomizedBrush(item->brush()));
        return item;
    } else if (type==GJ_MULTIPOINT){
        auto marker = circleMarker();
        GraphicsMultiPixmap *item = new GraphicsMultiPixmap(marker.first);
        item->setAnchor(marker.second);
        item->setPoints(fetchMultiGeometry<LatLng>(coords));
        return item;
    } else if(type==GJ_MULTILINE){
        GraphicsMultiLineString *item = new GraphicsMultiLineString(fetchMultiGeometry<LineString>(coords));
        item->setPen(randomizedPen(item->pen()));
        return item;
    } else if(type==GJ_MULTIPOLY){
        GraphicsMultiPolygon *item = new GraphicsMultiPolygon(fetchMultiGeometry<Polygon>(coords));
        item->setPen(randomizedPen(item->pen()));
        item->setBrush(randomizedBrush(item->brush()));
        return item;
    }
}
