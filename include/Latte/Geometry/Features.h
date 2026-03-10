#pragma once

#include "Latte/Geometry/LatLng.h"
#include "Latte/Geometry/LineString.h"
#include "Latte/Geometry/Polygon.h"

#include "Latte/Utils/Variant.hpp"
#include "Latte/Utils/VariantTree.hpp"

/**
 * @brief Abstract feature
 * 
 */
class BFeature{
    public:
        using Properties = VariantTree<int,double,bool,QString>;
    public:
        BFeature(const Properties &properties = {}) : properties(properties) {

        }

        Properties properties;
};

QDebug operator<<(QDebug debug,const BFeature::Properties::Value &obj);
QDebug operator<<(QDebug debug,const BFeature::Properties::Node &obj);

class Feature: public BFeature{
    public:
        using GeometryVar = Variant<
            LatLng,
            LineString,
            Polygon,
            MultiPoint,
            MultiLineString,
            MultiPolygon
        >;

    public:
        Feature(GeometryVar geometry, const Properties &properties = {}) : BFeature(properties), geometry(geometry) {

        }

        GeometryVar geometry;

};

QDebug operator<<(QDebug debug,const Feature &obj);

class FeatureCollection: public QVector<Feature>, public BFeature{
    public:
        using QVector<Feature>::QVector;

        FeatureCollection(const QVector<Feature> &features, const Properties &properties) : BFeature(properties), QVector<Feature>(features) {

        }
};

QDebug operator<<(QDebug debug,const FeatureCollection &obj);