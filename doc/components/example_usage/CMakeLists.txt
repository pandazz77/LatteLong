cmake_minimum_required(VERSION 4.2)

find_package(LatteLong REQUIRED COMPONENTS LatteFoo)
find_package(Qt6 REQUIRED COMPONENTS 
    Core
    Widgets
)

add_executable(ExampleFoo main.cpp)
target_link_libraries(ExampleFoo LatteLong::LatteLong LatteLong::LatteFoo)