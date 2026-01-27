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

    src/Graphics/Items/LGraphicsItem.cpp
    src/Graphics/Items/LGraphicsShape.cpp
    src/Graphics/Items/LGraphicsPath.cpp
    src/Graphics/Items/LGraphicsLineString.cpp
    src/Graphics/Items/LGraphicsPolygon.cpp

    src/main.cpp
)

set(HDRS
    include/Structs/LatLng.h
    include/Structs/LineString.h
    include/Structs/Polygon.h
    include/Structs/Bounds.h

    include/Projection/GeometryConvertor.h
    include/Projection/IProjection.hpp
    include/Projection/SimpleProjection.hpp
    include/Projection/Mercator.hpp
    include/Projection/SphericalMercator.hpp

    include/Graphics/View/MapGraphicsScene.hpp
    include/Graphics/Items/LGraphicsItem.h
    include/Graphics/Items/LGraphicsShape.h
    include/Graphics/Items/LGraphicsPath.h
    include/Graphics/Items/LGraphicsLineString.h
    include/Graphics/Items/LGraphicsPolygon.h
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