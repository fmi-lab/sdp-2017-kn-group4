include_directories(${PROJECT_SOURCE_DIR}/inc)
set(SOURCE_FILES main.cpp calculator.cpp)
add_executable(calculator ${SOURCE_FILES})
add_library(calculator_lib STATIC ${SOURCE_FILES})
