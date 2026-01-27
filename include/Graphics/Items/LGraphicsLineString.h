#pragma once

#include "LGraphicsPath.h"
#include "LineString.h"

class LGraphicsLineString: public LGraphicsPath{
    public:
        LGraphicsLineString(LGraphicsItem *parent = nullptr);
        LGraphicsLineString(const LineString &line, LGraphicsItem *parent = nullptr);

        void setLine(const LineString &line);
        LineString line() const;

        QPainterPath path(const IProjection *proj) const override;

        void setBrush(const QBrush &brush) = delete;
        QBrush brush() const = delete;

    private:
        LineString _line;
};