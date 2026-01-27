#include "Polygon.h"


Polygon::Polygon(LineString exterior, QVector<LineString> interiors) 
: exterior(encloseLine(exterior)) {
    for(auto interior: interiors)
        interiors.push_back(encloseLine(interior));
}

LineString Polygon::encloseLine(LineString line){
    if(line.cbegin()!=line.cend()) 
        line.push_back(line.front());
    return line;
}