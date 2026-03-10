#include "Latte/Geometry/Features.h"

#include <QDebug>
#include <qdebug.h>

void _debug_node(QDebug &debug, const BFeature::Properties::Node &node){
    const auto kv_range = node.asKeyValueRange();
    debug.nospace() << "{";
    for(auto it = kv_range.begin(); it != kv_range.end(); ++it){
        debug.nospace() << it->first << " : " << it->second;
        if(std::next(it)!=kv_range.end())
            debug.nospace() << ", ";
    }
    debug.nospace() << "}";
}

void _debug_list(QDebug &debug, const BFeature::Properties::List &list){
    debug.nospace() << "{";
    for(auto it = list.begin(); it != list.end(); ++it){
        debug.nospace() << *it;
        if(std::next(it)!=list.end())
            debug.nospace() << ", ";
    }
    debug.nospace() << "}";
}

// Debug Properties value
QDebug operator<<(QDebug debug,const BFeature::Properties::Value &obj){
    QDebugStateSaver saver(debug);
    if(const int *val = obj.getIf<int>()){
        debug.nospace() << *val;
    } else if(const double *val = obj.getIf<double>()){
        debug.nospace() << *val;
    } else if(const bool *val = obj.getIf<bool>()){
        debug.nospace() << *val;
    } else if(const QString *val = obj.getIf<QString>()){
        debug.nospace() << *val;
    } else if(const BFeature::Properties::List *val = obj.getIf<BFeature::Properties::List>()){
        _debug_list(debug,*val);
    } else if(const BFeature::Properties::Node *val = obj.getIf<BFeature::Properties::Node>()){
        _debug_node(debug,*val);
    }
    return debug;
}

// Debug Properties node
QDebug operator<<(QDebug debug,const BFeature::Properties::Node &obj){
    QDebugStateSaver saver(debug);
    _debug_node(debug,obj);
    return debug;
}

// Debug Geometry variant
QDebug operator<<(QDebug debug,const Feature::GeometryVar &obj){
    QDebugStateSaver saver(debug);
    std::visit([&debug](auto &&geom){
        debug.nospace() << geom;
    },obj);
    return debug;
}

// Debug Feature
QDebug operator<<(QDebug debug,const Feature &obj){
    QDebugStateSaver saver(debug);
    debug.nospace() 
        << "Feature("
            << obj.geometry
            << ", "
            << "Properties("
                << obj.properties
            << ")"
        << ")";
    return debug;
}

// Debug Feature Collection
QDebug operator<<(QDebug debug,const FeatureCollection &obj){
    QDebugStateSaver saver(debug);
    debug.nospace() << "FeatureCollection(";
    for(auto it = obj.begin(); it != obj.end(); it++ ){
        debug.nospace() << *it;
        if(std::next(it)!=obj.end())
            debug.nospace() << ", ";
    }
    debug.nospace() << ")";
    return debug;
}