#pragma once

#include "LGraphicsPath.hpp"
#include "LineString.hpp"

#include "GeometryConvertor.h"

class LGraphicsLineString: public LGraphicsPath{
    public:
        LGraphicsLineString(LGraphicsItem *parent = nullptr) : LGraphicsPath(parent) {}
        LGraphicsLineString(const LineString &line, LGraphicsItem *parent = nullptr) : LGraphicsLineString(parent){
            setLine(line);
        }

        void setLine(const LineString &line){
            _line = line;
            updatePathCache();
        }

        LineString line() const{
            return _line;
        }

        QPainterPath path(const IProjection *proj) const override {
            return GeometryConvertor::line(_line,proj);
        }

        void setBrush(const QBrush &brush) = delete;
        QBrush brush() const = delete;

    private:
        LineString _line;
};