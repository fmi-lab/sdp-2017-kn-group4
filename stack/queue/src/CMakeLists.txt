include_directories(${PROJECT_SOURCE_DIR}/inc)
set(SOURCE_FILES queue.cpp)
add_library(queue_lib STATIC ${SOURCE_FILES})
