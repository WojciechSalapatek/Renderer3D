
project(Renderer)

set(HEDEAR_FILES Obj.h)
set(SOURCE_FILES Obj.cpp Interpolator.cpp Interpolator.h)

add_library(libutil
        STATIC ${SOURCE_FILES}
        )
target_include_directories(libutil
        PUBLIC .)



