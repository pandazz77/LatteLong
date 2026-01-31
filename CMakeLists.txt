cmake_minimum_required(VERSION 3.16)
project(LatteLong VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

    src/Providers/VectorProvider.cpp
    src/Providers/GeoJsonProvider.cpp
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

    include/Providers/VectorProvider.h
    include/Providers/GeoJsonProvider.h
)

SET(INCLUDES
    Geometry
    Projection
    Graphics/Items
    Graphics/View
    Providers
)

find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Widgets    
)

SET(LIBS 
    Qt6::Core
    Qt6::Widgets
)

add_library(${PROJECT_NAME} ${SRCS} ${HDRS})
target_link_libraries(${PROJECT_NAME} ${LIBS})
foreach(subdir IN LISTS INCLUDES)
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${subdir}>"
        "$<INSTALL_INTERFACE:include/${subdir}>"
    )
endforeach()

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    EXPORT LatteLongTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING 
        PATTERN "*.h" 
        PATTERN "*.hpp"
)

install(EXPORT LatteLongTargets
    FILE LatteLongConfig.cmake
    NAMESPACE LatteLong::
    DESTINATION lib/cmake/LatteLong
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/LatteLongConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/LatteLongConfig.cmake"
    INSTALL_DESTINATION lib/cmake/LatteLong
)

# ---------------- uninstall target ----------------
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
# --------------------------------------------------

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_subdirectory(./tests)
endif()