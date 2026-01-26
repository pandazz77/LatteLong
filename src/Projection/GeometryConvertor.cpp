#include "GeometryConvertor.h"

#include "GeometryConvertor.h"

QPointF GeometryConvertor::point(const LatLng &pos,const IProjection *proj){
    return proj->project(pos);
}

QVector<QPointF> GeometryConvertor::simpleLine(const LineString &line, const IProjection *proj){
    QVector<QPointF> pointVector;
    for(const LatLng &latLng: line){
        pointVector.push_back(point(latLng,proj));
    }
    return pointVector;
}

QPainterPath GeometryConvertor::line(const LineString &line, const IProjection *proj){
    QVector<QPointF> simple = simpleLine(line,proj);
    QPainterPath linePath(simple.constFirst());

    for(int i = 1; i < simple.size(); i++){
        linePath.lineTo(simple[i]);
    }

    return linePath;
}

QPainterPath GeometryConvertor::polygon(const Polygon &poly, const IProjection *proj){
    QPainterPath polyPath;

    QPolygonF exterior = ensurePolygonOrder(simpleLine(poly.exterior,proj),true);
    polyPath.addPolygon(exterior);
    for(auto interiorRaw: poly.interiors){
        QPolygonF interior = ensurePolygonOrder(simpleLine(interiorRaw,proj),false);
        polyPath.addPolygon(interior);
    }
    polyPath.setFillRule(Qt::OddEvenFill);

    return polyPath;
}

bool GeometryConvertor::isClockwise(const QPolygonF &polygon) {
    double sum = 0.0;
    int n = polygon.size();

    for (int i = 0; i < n; ++i) {
        const QPointF &p1 = polygon[i];
        const QPointF &p2 = polygon[(i + 1) % n];
        sum += (p2.x() - p1.x()) * (p2.y() + p1.y());
    }

    return sum > 0;
}

QPolygonF GeometryConvertor::reversePolygon(const QPolygonF &polygon) {
    QPolygonF reversed = polygon;
    std::reverse(reversed.begin(), reversed.end());
    return reversed;
}

QPolygonF GeometryConvertor::ensurePolygonOrder(const QPolygonF &polygon, bool clockwise) {
    if ((isClockwise(polygon) && !clockwise) || (!isClockwise(polygon) && clockwise)) {
        return reversePolygon(polygon);
    }
    return polygon;
}