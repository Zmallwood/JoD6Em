cmake_minimum_required (VERSION 3.30)
project (JoDServer)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-flto=auto")
file(GLOB_RECURSE sources ../src/**.cpp)
list(FILTER sources EXCLUDE REGEX ".*.inc.cpp$")
file(GLOB_RECURSE sources_shared ../../shared/src/**.cpp)
add_executable(JoDServer 
    ${sources}
    ${sources_shared}
)
target_include_directories(JoDServer PRIVATE ../src ../../shared/src /usr/include/python3.12/)

target_precompile_headers(JoDServer PRIVATE ../src/stdafx.h)
target_link_libraries(JoDServer python3.12)