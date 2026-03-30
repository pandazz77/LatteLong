#pragma once

#include "Latte/Geometry/Features.h"
#include "Latte/Graphics/Items/GraphicsItem.h"

namespace FeatureGraphicsFactory{
    GraphicsItem *fromFeature(const Feature &feature);
    Feature toFeature(GraphicsItem *item);
};