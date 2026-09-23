cmake_minimum_required(VERSION 3.15)
project(au_ttfparser CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
    au_ttfparser
    src/ttfparser.cpp
)

target_include_directories(au_ttfparser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(test_run tests/test_main.cpp)
target_link_libraries(test_run PRIVATE au_ttfparser)
