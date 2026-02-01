#include "Latte/Projection/SimpleProjection.h"

QPointF SimpleProjection::project(const LatLng &latlng) const {
    return QPointF(latlng.lng(),latlng.lat());
}
LatLng SimpleProjection::unproject(const QPointF &point) const {
    return LatLng(point.y(),point.x());
}

Bounds SimpleProjection::bounds() const {
    return {
        LatLng(90,180),
        LatLng(-90,-180)
    };
}