cmake_minimum_required(VERSION 3.18.2)
project(Path-Tracer)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(Path-Tracer PUBLIC OpenMP::OpenMP_CXX)
endif()

set(SOURCES src/Main.cpp src/World.cpp src/RenderObjects/RenderObject.cpp src/RenderObjects/Plane.cpp src/RenderObjects/Sphere.cpp)

add_executable(Path-Tracer ${SOURCES})
