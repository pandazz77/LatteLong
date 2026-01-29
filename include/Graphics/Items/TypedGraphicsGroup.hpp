#pragma once

#include "GraphicsGroup.h"

// TG is graphicsItem type
template<typename TG>
class TypedGraphicsGroup: public GraphicsGroup {
    public:
        TypedGraphicsGroup(GraphicsItem *parent = nullptr) : GraphicsGroup(parent) { }
        TypedGraphicsGroup(QVector<TG*> items, GraphicsItem *parent = nullptr) : GraphicsGroup(items, parent) { }


        void add(TG *item) { GraphicsGroup::add(item); }
        void add(QVector<TG*> items) { GraphicsGroup::add(items); }
        void remove(TG *item, bool removeFromScene = true) { GraphicsGroup::remove(item,removeFromScene); }
        void remove(QVector<TG*> items, bool removeFromScene = true) { GraphicsGroup::remove(items,removeFromScene); }

        QList<TG*> items() const { 
            QVector<TG*> result;
            for(auto item: GraphicsGroup::items())
                result.push_back(dynamic_cast<TG*>(item));
            return result;
        }
};