#include "Latte/Providers/GeoJsonProvider.h"

#include "Latte/Graphics/Items/GraphicsPixmap.h"
#include "Latte/Graphics/Items/GraphicsLineString.h"
#include "Latte/Graphics/Items/GraphicsPolygon.h"

#include <QFile>

#define GJ_FEATURE "Feature"
#define GJ_FEATURECOLLECTION "FeatureCollection"
#define GJ_POINT "Point"
#define GJ_LINE "LineString"
#define GJ_POLY "Polygon"
#define GJ_MULTIPOINT "MultiPoint"
#define GJ_MULTILINE "MultiLineString"
#define GJ_MULTIPOLY "MultiPolygon"

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

GeoJsonProvider::GeoJsonProvider() : VectorProvider() {
    
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
    GraphicsItem *result = nullptr;
    if(type == GJ_FEATURE) 
        result = processFeature(map);
    else if(type == GJ_FEATURECOLLECTION)
        result = processFeatureCollection(map);
    else
        qWarning() << "Undefined geojson type:" << type;
    
    if(map.contains("properties"))
        result->setData(0,map["properties"]);

    return result;
}

GraphicsItem *GeoJsonProvider::processFeature(QVariantMap map){
    assert(map["type"].toString() == GJ_FEATURE);

    GraphicsItem *item = createItemFromGeometry(map["geometry"].toMap());
    QVariant data;
    if(map.contains("properties"))
        data = map["properties"];
    VectorProvider::onNewLayer(item,data);

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
        GraphicsPixmap *item = new GraphicsPixmap();
        item->setGPos(fetchGeometry<LatLng>(coords));
        return item;
    } else if(type==GJ_LINE){
        GraphicsLineString *item = new GraphicsLineString(fetchGeometry<LineString>(coords));
        return item;
    } else if(type==GJ_POLY){
        GraphicsPolygon *item = new GraphicsPolygon(fetchGeometry<Polygon>(coords));
        return item;
    } else if (type==GJ_MULTIPOINT){
        GraphicsMultiPixmap *item = new GraphicsMultiPixmap();
        item->setPoints(fetchMultiGeometry<LatLng>(coords));
        return item;
    } else if(type==GJ_MULTILINE){
        GraphicsMultiLineString *item = new GraphicsMultiLineString(fetchMultiGeometry<LineString>(coords));
        return item;
    } else if(type==GJ_MULTIPOLY){
        GraphicsMultiPolygon *item = new GraphicsMultiPolygon(fetchMultiGeometry<Polygon>(coords));
        return item;
    }
}
