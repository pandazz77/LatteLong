#pragma once

#include "Latte/Utils/Variant.hpp"

#include <QVector>
#include <QMap>

template<typename ...Types>
class VariantTreeNode;

template<typename ...Types>
class VariantList;

template<typename ...Types>
class VariantTreeValue: public Variant<Types...,VariantTreeNode<Types...>,VariantList<Types...>>{
    public:
        using Variant<Types...,VariantTreeNode<Types...>,VariantList<Types...>>::Variant;
};

template<typename ...Types>
class VariantList: public QVector<VariantTreeValue<Types...>>{
    public:
        using QVector<VariantTreeValue<Types...>>::QVector;
};

template<typename ...Types>
class VariantTreeNode: public QMap<QString,VariantTreeValue<Types...>>{
    public:
        using Value = VariantTreeValue<Types...>;
        using List = VariantList<Types...>;
        using Node = VariantTreeNode<Types...>;

        using QMap<QString,VariantTreeValue<Types...>>::QMap;
};

template<typename ...Types>
using VariantTree = VariantTreeNode<Types...>;