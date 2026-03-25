#include "simple_dataset.hpp"

#include "Latte/Geometry/Features.h"

#include <QDebug>

int main(int argc, char *argv[]){

    Feature feature_point(pointTest,{
        {"name","SamplePoint"},
        {"int_val",0},
        {"double_val",3.14},
        {"flag",false},
        {"list",Feature::Properties::List{1,2,3,4}},
        {"sub_props",Feature::Properties::Node{
            {"sub_prop_int",1},
            {"sub_prop_double",3.14}
        }}
    });
    Feature feature_line(lineTest,{
        {"name","SampleLine"},
        {"int_val",0},
        {"double_val",3.14},
        {"flag",false},
        {"list",Feature::Properties::List{1,2,3,4}},
        {"sub_props",Feature::Properties::Node{
            {"sub_prop_int",1},
            {"sub_prop_double",3.14}
        }}
    });
    Feature feature_poly(polyTest,{
        {"name","SamplePoly"},
        {"int_val",0},
        {"double_val",3.14},
        {"flag",false},
        {"list",Feature::Properties::List{1,2,3,4}},
        {"sub_props",Feature::Properties::Node{
            {"sub_prop_int",1},
            {"sub_prop_double",3.14}
        }}
    });
    Feature feature_mpoint(mutliPointTest,{
        {"name","SampleMultiPoint"},
        {"int_val",0},
        {"double_val",3.14},
        {"flag",false},
        {"list",Feature::Properties::List{1,2,3,4}},
        {"sub_props",Feature::Properties::Node{
            {"sub_prop_int",1},
            {"sub_prop_double",3.14}
        }}
    });
    Feature feature_mline(multiLineTest,{
        {"name","SampleMultiLine"},
        {"int_val",0},
        {"double_val",3.14},
        {"flag",false},
        {"list",Feature::Properties::List{1,2,3,4}},
        {"sub_props",Feature::Properties::Node{
            {"sub_prop_int",1},
            {"sub_prop_double",3.14}
        }}
    });
    Feature feature_mpoly(multiPolyTest,{
        {"name","SampleMultiPoly"},
        {"int_val",0},
        {"double_val",3.14},
        {"flag",false},
        {"list",Feature::Properties::List{1,2,3,4}},
        {"sub_props",Feature::Properties::Node{
            {"sub_prop_int",1},
            {"sub_prop_double",3.14}
        }}
    });

    FeatureCollection feature_collection{{
        feature_point,
        feature_line,
        feature_poly,
        feature_mpoint,
        feature_mline,
        feature_mpoly
    }, {
        {"name","SampleFeatureCollection"},
        {"int_val",0},
        {"double_val",3.14},
        {"flag",false},
        {"list",Feature::Properties::List{1,2,3,4}},
        {"sub_props",Feature::Properties::Node{
            {"sub_prop_int",1},
            {"sub_prop_double",3.14}
        }}
    }};

    qDebug() << "Feature properties:";
    qDebug() << feature_point.properties;

    qDebug() << "";

    qDebug() << "Feature point:";
    qDebug() << feature_point;

    qDebug() << "";

    qDebug() << "FeatureCollection:";
    qDebug() << feature_collection;

    
    // Getting feature properties =============
    int int_val = feature_point.properties["int_val"].to<int>(); // 0
    int list_val = feature_point.properties["list"][0].to<int>(); // 1
    int node_val = feature_point.properties["sub_props"]["sub_prop_int"].to<int>(); // 1
    
    assert(int_val==0);
    assert(list_val==1);
    assert(node_val==1);
    // =========================================

    // Setting feature properties ==============
    feature_point.properties["int_val"] = 77;
    feature_point.properties["list"][0] = 88;
    feature_point.properties["sub_props"]["sub_props_int"] = 99;

    assert(feature_point.properties["int_val"].to<int>() == 77);
    assert(feature_point.properties["list"][0].to<int>() == 88);
    assert(feature_point.properties["sub_props"]["sub_props_int"].to<int>() == 99);
    // =========================================


}