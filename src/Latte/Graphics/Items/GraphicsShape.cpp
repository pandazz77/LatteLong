#include "Latte/Graphics/Items/GraphicsShape.h"

IGraphicsLine::IGraphicsLine(){
    _pen.setCosmetic(true);
}

void IGraphicsLine::setPen(const QPen &pen){
    _pen = pen;
}

QPen IGraphicsLine::pen() const {
    return _pen;
}

// ===========================

IGraphicsShape::IGraphicsShape(){
    _brush.setStyle(Qt::SolidPattern);
}

void IGraphicsShape::setBrush(const QBrush &brush){
    _brush = brush;
}

QBrush IGraphicsShape::brush() const {
    return _brush;
}