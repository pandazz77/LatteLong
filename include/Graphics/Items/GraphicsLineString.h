#pragma once

#include "GraphicsPath.h"
#include "LineString.h"

class GraphicsLineString: public GraphicsPath{
    public:
        GraphicsLineString(GraphicsItem *parent = nullptr);
        GraphicsLineString(const LineString &line, GraphicsItem *parent = nullptr);

        void setLine(const LineString &line);
        LineString line() const;

        QPainterPath path(const IProjection *proj) const override;

        void setBrush(const QBrush &brush) = delete;
        QBrush brush() const = delete;

    private:
        LineString _line;
};