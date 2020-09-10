cmake_minimum_required(VERSION 3.18.2)
project(Path-Tracer)

set(SOURCES src/Main.cpp src/World.cpp src/RenderObjects/RenderObject.cpp src/RenderObjects/Plane.cpp src/RenderObjects/Sphere.cpp)

add_executable(Path-Tracer ${SOURCES})
