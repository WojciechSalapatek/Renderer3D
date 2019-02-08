
project(Renderer)

set(HEDEAR_FILES Vector4D.h
        Point.h Edge.h)
set(SOURCE_FILES
        Point.cpp Vector4D.cpp Vector4D.h Matrix.cpp Matrix.h Edge.cpp)

add_library(libcontext
        STATIC ${SOURCE_FILES}
        )
target_include_directories(libcontext
        PUBLIC .)



