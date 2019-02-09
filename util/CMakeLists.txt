
project(Renderer)

set(HEDEAR_FILES Obj.h)
set(SOURCE_FILES Obj.cpp)

add_library(libutil
        STATIC ${SOURCE_FILES}
        )
target_include_directories(libutil
        PUBLIC .)



