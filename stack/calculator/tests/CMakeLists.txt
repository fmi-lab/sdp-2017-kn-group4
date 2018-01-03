add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE ${PROJECT_SOURCE_DIR}/lib/doctest)

include_directories(${PROJECT_SOURCE_DIR}/inc)
add_executable(tests main.cpp calculator_tests.cpp)
target_link_libraries(tests doctest calculator_lib)
