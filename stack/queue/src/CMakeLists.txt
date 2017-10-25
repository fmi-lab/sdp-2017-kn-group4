include_directories(${PROJECT_SOURCE_DIR}/inc)
set(SOURCE_FILES main.cpp queue.cpp)
add_executable(queue ${SOURCE_FILES})
add_library(queue_lib STATIC ${SOURCE_FILES})
