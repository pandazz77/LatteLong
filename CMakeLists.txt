cmake_minimum_required(VERSION 3.5)
project(LatteLong VERSION 0.0.1)

set(CMAKE_AUTOMOC ON)

set(SRCS
    src/Geometry/LatLng.cpp
    src/Geometry/LineString.cpp
    src/Geometry/Polygon.cpp
    src/Geometry/Bounds.cpp
    src/Geometry/MultiGeometry.cpp

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
    src/Graphics/Items/GraphicsGroup.cpp
)

set(HDRS
    include/Geometry/LatLng.h
    include/Geometry/LineString.h
    include/Geometry/Polygon.h
    include/Geometry/Bounds.h
    include/Geometry/MultiGeometry.h

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
    include/Graphics/Items/GraphicsGroup.h
    include/Graphics/Items/TypedGraphicsGroup.hpp
)

SET(INCLUDES
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

add_library(${PROJECT_NAME} ${SRCS} ${HDRS})
target_link_libraries(${PROJECT_NAME} ${LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_subdirectory(./tests)
endif()