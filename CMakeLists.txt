cmake_minimum_required(VERSION 3.16)
project(LatteLong VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

set(SRCS
    src/Latte/Geometry/LatLng.cpp
    src/Latte/Geometry/LineString.cpp
    src/Latte/Geometry/Polygon.cpp
    src/Latte/Geometry/Bounds.cpp
    src/Latte/Geometry/MultiGeometry.cpp

    src/Latte/Projection/LocalCoordinateSystem.cpp
    src/Latte/Projection/GeometryConvertor.cpp
    src/Latte/Projection/SimpleProjection.cpp
    src/Latte/Projection/Mercator.cpp
    src/Latte/Projection/SphericalMercator.cpp

    src/Latte/Graphics/View/MapGraphicsScene.cpp
    src/Latte/Graphics/View/MapGraphicsView.cpp

    src/Latte/Graphics/Items/GraphicsItem.cpp
    src/Latte/Graphics/Items/GraphicsShape.cpp
    src/Latte/Graphics/Items/GraphicsPath.cpp
    src/Latte/Graphics/Items/GraphicsLineString.cpp
    src/Latte/Graphics/Items/GraphicsPolygon.cpp
    src/Latte/Graphics/Items/GraphicsPixmap.cpp
    src/Latte/Graphics/Items/GraphicsGroup.cpp

    src/Latte/Providers/VectorProvider.cpp
    src/Latte/Providers/GeoJsonProvider.cpp
)

set(HDRS
    include/Latte/Geometry/LatLng.h
    include/Latte/Geometry/LineString.h
    include/Latte/Geometry/Polygon.h
    include/Latte/Geometry/Bounds.h
    include/Latte/Geometry/MultiGeometry.h

    include/Latte/Projection/LocalCoordinateSystem.h
    include/Latte/Projection/GeometryConvertor.h
    include/Latte/Projection/IProjection.hpp
    include/Latte/Projection/SimpleProjection.h
    include/Latte/Projection/Mercator.h
    include/Latte/Projection/SphericalMercator.h

    include/Latte/Graphics/View/MapGraphicsScene.h
    include/Latte/Graphics/View/MapGraphicsView.h
    
    include/Latte/Graphics/Items/GraphicsItem.h
    include/Latte/Graphics/Items/GraphicsShape.h
    include/Latte/Graphics/Items/GraphicsPath.h
    include/Latte/Graphics/Items/GraphicsLineString.h
    include/Latte/Graphics/Items/GraphicsPolygon.h
    include/Latte/Graphics/Items/GraphicsPixmap.h
    include/Latte/Graphics/Items/GraphicsGroup.h
    include/Latte/Graphics/Items/TypedGraphicsGroup.hpp

    include/Latte/Providers/VectorProvider.h
    include/Latte/Providers/GeoJsonProvider.h
)

find_package(Qt6 REQUIRED COMPONENTS 
    Core
    Widgets
)

add_library(${PROJECT_NAME} ${SRCS} ${HDRS})
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt6::Core
        Qt6::Widgets
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)



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