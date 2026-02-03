#include "Latte/Projection/GeometryConvertor.h"

GeometryConvertor::GeometryConvertor(const IProjection *proj){
    setProjection(proj);
}

void GeometryConvertor::setProjection(const IProjection *proj){
    _proj = proj;
}

const IProjection *GeometryConvertor::projection() const {
    return _proj;
}

QPointF GeometryConvertor::point(const LatLng &pos) const {
    QPointF projected = _proj->project(pos);
    return lcs.toLocal(projected);
}

QVector<QPointF> GeometryConvertor::simpleLine(const LineString &line) const {
    QVector<QPointF> pointVector;
    for(const LatLng &latLng: line){
        pointVector.push_back(point(latLng));
    }
    return pointVector;
}

QPainterPath GeometryConvertor::line(const LineString &line) const {
    QVector<QPointF> simple = simpleLine(line);
    QPainterPath linePath(simple.constFirst());

    for(int i = 1; i < simple.size(); i++){
        linePath.lineTo(simple[i]);
    }

    return linePath;
}

QPainterPath GeometryConvertor::polygon(const Polygon &poly) const {
    QPainterPath polyPath;

    QPolygonF exterior = ensurePolygonOrder(simpleLine(poly.exterior),true);
    polyPath.addPolygon(exterior);
    for(auto interiorRaw: poly.interiors){
        QPolygonF interior = ensurePolygonOrder(simpleLine(interiorRaw),false);
        polyPath.addPolygon(interior);
    }
    polyPath.setFillRule(Qt::OddEvenFill);

    return polyPath;
}

QRectF GeometryConvertor::bounds(const Bounds &bounds) const {
    return QRectF(
        point(bounds.NW()),
        point(bounds.SE())
    );
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