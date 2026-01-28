#include "GraphicsShape.h"


GraphicsShape::GraphicsShape(GraphicsItem *parent) : GraphicsItem(parent), _pen(Qt::black), _brush(Qt::NoBrush){
    _pen.setCosmetic(true);
}

void GraphicsShape::setPen(const QPen &pen){
    _pen = pen;
}

void GraphicsShape::setBrush(const QBrush &brush){
    _brush = brush;
}

QPen GraphicsShape::pen() const {
    return _pen;
}

QBrush GraphicsShape::brush() const {
    return _brush;
}