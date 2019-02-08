
project(Renderer)

set(HEDEAR_FILES
        Bitmap.h)
set(SOURCE_FILES
        Bitmap.cpp )

add_library(libbitmap
        STATIC ${SOURCE_FILES}
        )
target_include_directories(libbitmap
        PUBLIC .)

