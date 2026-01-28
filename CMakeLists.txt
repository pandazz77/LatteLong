cmake_minimum_required(VERSION 3.5)
project(LatteLong)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SRCS
    src/Geometry/LatLng.cpp
    src/Geometry/LineString.cpp
    src/Geometry/Polygon.cpp
    src/Geometry/Bounds.cpp

    src/Projection/GeometryConvertor.cpp
    src/Projection/SimpleProjection.cpp
    src/Projection/Mercator.cpp
    src/Projection/SphericalMercator.cpp

    src/Graphics/View/MapGraphicsScene.cpp
    src/Graphics/View/MapGraphicsView.cpp

    src/Graphics/Items/GraphicsItem.cpp
    src/Graphics/Items/GraphicsShape.cpp
    src/Graphics/Items/GraphicsPath.cpp
    src/Graphics/Items/GraphicsLineString.cpp
    src/Graphics/Items/GraphicsPolygon.cpp
    src/Graphics/Items/GraphicsPixmap.cpp

    src/main.cpp
)

set(HDRS
    include/Geometry/LatLng.h
    include/Geometry/LineString.h
    include/Geometry/Polygon.h
    include/Geometry/Bounds.h

    include/Projection/GeometryConvertor.h
    include/Projection/IProjection.hpp
    include/Projection/SimpleProjection.h
    include/Projection/Mercator.h
    include/Projection/SphericalMercator.h

    include/Graphics/View/MapGraphicsScene.h
    include/Graphics/View/MapGraphicsView.h
    
    include/Graphics/Items/GraphicsItem.h
    include/Graphics/Items/GraphicsShape.h
    include/Graphics/Items/GraphicsPath.h
    include/Graphics/Items/GraphicsLineString.h
    include/Graphics/Items/GraphicsPolygon.h
    include/Graphics/Items/GraphicsPixmap.h
)

include_directories(
    include/Geometry
    include/Projection
    include/Graphics/Items
    include/Graphics/View
)

find_package(Qt6 COMPONENTS 
    Core 
    Widgets 

    REQUIRED
)

SET(LIBS 
    Qt6::Core
    Qt6::Widgets
)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})
target_link_libraries(${PROJECT_NAME} ${LIBS})