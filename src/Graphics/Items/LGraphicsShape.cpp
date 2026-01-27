#include "LGraphicsShape.h"


LGraphicsShape::LGraphicsShape(LGraphicsItem *parent) : LGraphicsItem(parent), _pen(Qt::black), _brush(Qt::NoBrush){
    _pen.setCosmetic(true);
}

void LGraphicsShape::setPen(const QPen &pen){
    _pen = pen;
}

void LGraphicsShape::setBrush(const QBrush &brush){
    _brush = brush;
}

QPen LGraphicsShape::pen() const {
    return _pen;
}

QBrush LGraphicsShape::brush() const {
    return _brush;
}