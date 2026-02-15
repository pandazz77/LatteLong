cmake_minimum_required(VERSION 4.2)
project(LatteFoo)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
)
find_package(LatteLong)
find_package(SOME_DEPENDENCY)

set(SRCS
    src/Latte/Geometry/FooGeometry.cpp
)

set(HDRS
    include/Latte/Geometry/FooGeometry.h
)

add_library(${PROJECT_NAME} SHARED ${SRCS} ${HDRS})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt6::Core
        Qt6::Widgets
        LatteLong::LatteLong
        SOME_DEPENDENCY::SOME_DEPENDENCY
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS ${PROJECT_NAME}
    EXPORT "LatteLong${PROJECT_NAME}Targets"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.inl"
)

install(EXPORT "LatteLong${PROJECT_NAME}Targets"
    FILE "LatteLong${PROJECT_NAME}Targets.cmake"
    NAMESPACE LatteLong::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LatteLong
)

include(CMakePackageConfigHelpers)


# EXTRA IS OPTIONAL
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/LatteLong${PROJECT_NAME}Extra.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/LatteLong${PROJECT_NAME}Extra.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/LatteLong${PROJECT_NAME}Extra.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LatteLong
)
