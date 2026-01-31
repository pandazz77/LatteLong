#pragma once

#include "GraphicsItem.h"
#include "GraphicsGroup.h"
#include "VectorProvider.h"

#include "LatLng.h"
#include "LineString.h"
#include "Polygon.h"

#include <QJsonDocument>

class GeoJsonProvider : public VectorProvider{
    public:
        GeoJsonProvider();

        GraphicsGroup *load(const QJsonDocument &doc);
        GraphicsGroup *fromFile(const QString &filePath);

        GraphicsItem *processSomeFeature(QVariantMap map); // process feature or feature collection
        GraphicsItem *processFeature(QVariantMap map); // process single feature
        GraphicsGroup *processFeatureCollection(QVariantMap map); // process feature collection

        static GraphicsItem *createItemFromGeometry(QVariantMap map);

        template<typename TGeometry>
        static TGeometry fetchGeometry(QVariantList lngLatCoords);

        template<class TGeometry>
        static MultiGeometry<TGeometry> fetchMultiGeometry(QVariantList multiItems);

};