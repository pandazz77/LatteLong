cmake_minimum_required(VERSION 3.5)
project(LatteLong)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SRCS
    src/Structs/LatLng.cpp
    src/Structs/LineString.cpp
    src/Structs/Polygon.cpp
    src/Structs/Bounds.cpp

    src/Projection/GeometryConvertor.cpp
    src/Projection/SimpleProjection.cpp
    src/Projection/Mercator.cpp
    src/Projection/SphericalMercator.cpp

    src/Graphics/View/MapGraphicsScene.cpp
    src/Graphics/View/MapGraphicsView.cpp

    src/Graphics/Items/LGraphicsItem.cpp
    src/Graphics/Items/LGraphicsShape.cpp
    src/Graphics/Items/LGraphicsPath.cpp
    src/Graphics/Items/LGraphicsLineString.cpp
    src/Graphics/Items/LGraphicsPolygon.cpp
    src/Graphics/Items/LGraphicsPixmap.cpp

    src/main.cpp
)

set(HDRS
    include/Structs/LatLng.h
    include/Structs/LineString.h
    include/Structs/Polygon.h
    include/Structs/Bounds.h

    include/Projection/GeometryConvertor.h
    include/Projection/IProjection.hpp
    include/Projection/SimpleProjection.h
    include/Projection/Mercator.h
    include/Projection/SphericalMercator.h

    include/Graphics/View/MapGraphicsScene.h
    include/Graphics/View/MapGraphicsView.h
    
    include/Graphics/Items/LGraphicsItem.h
    include/Graphics/Items/LGraphicsShape.h
    include/Graphics/Items/LGraphicsPath.h
    include/Graphics/Items/LGraphicsLineString.h
    include/Graphics/Items/LGraphicsPolygon.h
    include/Graphics/Items/LGraphicsPixmap.h
)

include_directories(
    include/Structs
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