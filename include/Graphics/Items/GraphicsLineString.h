#pragma once

#include "GraphicsPath.h"
#include "LineString.h"
#include "TypedGraphicsGroup.hpp"

class GraphicsLineString: public GraphicsPath{
    public:
        GraphicsLineString(GraphicsItem *parent = nullptr);
        GraphicsLineString(const LineString &line, GraphicsItem *parent = nullptr);

        void setLine(const LineString &line);
        LineString line() const;

        QPainterPath path(const IProjection *proj) const override;

    private:
        LineString _line;
};

class GraphicsMultiLineString: public TypedGraphicsGroup<GraphicsLineString>, public IGraphicsLine{
    public:
        GraphicsMultiLineString(GraphicsItem *parent = nullptr);
        GraphicsMultiLineString(const MultiLineString &lines, GraphicsItem *parent = nullptr);

        void setPen(const QPen &pen) override;

        void setLines(const MultiLineString &lines);
        MultiLineString lines() const;
};