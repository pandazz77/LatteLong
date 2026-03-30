#include "Latte/Providers/FeatureGraphicsFactory.h"


#include "Latte/Graphics/Items/GraphicsPixmap.h"
#include "Latte/Graphics/Items/GraphicsLineString.h"
#include "Latte/Graphics/Items/GraphicsPolygon.h"

namespace FeatureGraphicsFactory{

GraphicsItem *fromFeature(const Feature &feature){
    GraphicsItem *item;
    if(const LatLng *geometry = feature.geometry.getIf<LatLng>()){
        item = new GraphicsPixmap();
        item->setGPos(*geometry);
    } else if(const MultiPoint *geometry = feature.geometry.getIf<MultiPoint>()){
        item = new GraphicsMultiPixmap();
        item->cast<GraphicsMultiPixmap*>()->setPoints(*geometry);
    } else if(const LineString *geometry = feature.geometry.getIf<LineString>()){
        GraphicsLineString *item = new GraphicsLineString(*geometry);
    } else if(const MultiLineString *geometry = feature.geometry.getIf<MultiLineString>()){
        GraphicsMultiLineString *item = new GraphicsMultiLineString(*geometry);
    } else if(const Polygon *geometry = feature.geometry.getIf<Polygon>()){
        GraphicsPolygon *item = new GraphicsPolygon(*geometry);
    } else if(const MultiPolygon *geometry = feature.geometry.getIf<MultiPolygon>()){
        GraphicsMultiPolygon *item = new GraphicsMultiPolygon(*geometry);
    } 
    item->data = feature.properties;
    return item;
}

Feature toFeature(GraphicsItem *item){
    if(GraphicsPixmap *item = item->cast<GraphicsPixmap*>()){
        return Feature(item->gPos(),item->data);
    } else if(GraphicsMultiPixmap *item = item->cast<GraphicsMultiPixmap*>()){
        return Feature(item->points(),item->data);
    } else if(GraphicsLineString *item = item->cast<GraphicsLineString*>()){
        return Feature(item->line(),item->data);
    } else if(GraphicsMultiLineString *item = item->cast<GraphicsMultiLineString*>()){
        return Feature(item->lines(),item->data);
    } else if(GraphicsPolygon *item = item->cast<GraphicsPolygon*>()){
        return Feature(item->polygon(),item->data);
    } else if(GraphicsMultiPolygon *item = item->cast<GraphicsMultiPolygon*>()){
        return Feature(item->polygons(),item->data);
    } else {
        // ...        
    }
}


};