#pragma once

#include "LineString.hpp"

class Polygon{
    public:
        Polygon(LineString exterior = {}, QVector<LineString> interiors = {}) 
        : exterior(encloseLine(exterior)) {
            for(auto interior: interiors)
                interiors.push_back(encloseLine(interior));
        }

        // returns LinearRing
        static LineString encloseLine(LineString line){
            if(line.cbegin()!=line.cend()) 
                line.push_back(line.front());
            return line;
        }

    // private:
        LineString exterior;
        QVector<LineString> interiors;
};