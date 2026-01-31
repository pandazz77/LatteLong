#pragma once

#include "GraphicsPath.h"
#include "LineString.h"
#include "TypedGraphicsGroup.hpp"

class GraphicsLineString: public GraphicsPath{
    public:
        enum { Type = BaseType + 2 };
        GraphicsLineString(GraphicsItem *parent = nullptr);
        GraphicsLineString(const LineString &line, GraphicsItem *parent = nullptr);

        void setLine(const LineString &line);
        LineString line() const;

        QPainterPath path(const IProjection *proj) const override;
        int type() const override;

    private:
        LineString _line;
};

class GraphicsMultiLineString: public TypedGraphicsGroup<GraphicsLineString>, public IGraphicsLine{
    public:
        enum { Type = GroupTypeOffset + GraphicsLineString::Type };
        GraphicsMultiLineString(GraphicsItem *parent = nullptr);
        GraphicsMultiLineString(const MultiLineString &lines, GraphicsItem *parent = nullptr);

        void setPen(const QPen &pen) override;

        void setLines(const MultiLineString &lines);
        MultiLineString lines() const;

        int type() const override;
};