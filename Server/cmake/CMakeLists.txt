cmake_minimum_required (VERSION 3.28.3)
project (JoDServer)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_CXX_FLAGS "-flto=auto -pthread")
set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always")
file(GLOB_RECURSE sources ../ServerSource/**.cpp)
list(FILTER sources EXCLUDE REGEX ".*.inc.cpp$")
file(GLOB_RECURSE sources_shared ../../Shared/SharedCommonSource/**.cpp ../../Shared/SharedNetSource/**.cpp ../../Shared/SharedWorldStructureSource/**.cpp)
add_executable(JoDServer 
    ${sources}
    ${sources_shared}
)
#target_include_directories(JoDServer PRIVATE ../ServerSource ../../Shared/SharedSource /usr/include/python3.12/)
target_include_directories(JoDServer PRIVATE ../ServerSource ../../Shared/SharedCommonSource ../../Shared/SharedNetSource ../../Shared/SharedWorldStructureSource)

target_precompile_headers(JoDServer PRIVATE ../ServerSource/StdAfx/StdAfx.hpp)
#target_link_libraries(JoDServer python3.12)
target_link_libraries(JoDServer pqxx pq)
