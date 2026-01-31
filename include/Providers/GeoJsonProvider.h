#pragma once

#include "GraphicsItem.h"
#include "GraphicsGroup.h"

#include "LatLng.h"
#include "LineString.h"
#include "Polygon.h"

#include <QJsonDocument>

namespace GeoJsonProvider{
    
    GraphicsGroup *load(const QJsonDocument &doc);
    GraphicsGroup *fromFile(const QString &filePath);

    GraphicsItem *processSomeFeature(QVariantMap map); // process feature or feature collection
    GraphicsItem *processFeature(QVariantMap map); // process single feature
    GraphicsGroup *processFeatureCollection(QVariantMap map); // process feature collection

    GraphicsItem *createItemFromGeometry(QVariantMap map);

    LatLng fetchPoint(QVariantList lngLatCoords);
    LineString fetchLine(QVariantList lngLatCoords);
    Polygon fetchPoly(QVariantList lngLatCoords);
    
    template<class TGeometry>
    MultiGeometry<TGeometry> fetchMultiGeometry(QVariantList lngLatCoords);
};