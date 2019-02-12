cmake_minimum_required(VERSION 3.9)
project(Renderer)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(bitmap)
add_subdirectory(context)
add_subdirectory(util)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(Renderer main.cpp bitmap/Bitmap.cpp bitmap/Bitmap.h context/Point.cpp
        context/Point.h context/Vector4D.h context/Vector4D.cpp context/Matrix.cpp
        context/Matrix.h context/Edge.h context/Edge.cpp util/Obj.cpp util/Obj.h
        context/Mesh.cpp context/Mesh.h util/Interpolator.cpp util/Interpolator.h
        context/Quaternion.cpp context/Quaternion.h context/Camera.cpp context/Camera.h)
target_link_libraries(Renderer ${SDL2_LIBRARIES})