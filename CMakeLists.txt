cmake_minimum_required(VERSION 3.15)
project(HPCExporter VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SOURCES
    src/main.cc
    src/collectors.cc
    src/webserver.cc
)
add_executable(HPCExporter ${SOURCES})
target_include_directories(HPCExporter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
