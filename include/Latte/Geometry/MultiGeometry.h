#pragma once

#include <QVector>

template<class TGeometry>
class MultiGeometry: public QVector<TGeometry>{
    public:
        using QVector<TGeometry>::QVector;
};