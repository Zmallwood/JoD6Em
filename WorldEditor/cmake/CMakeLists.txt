cmake_minimum_required (VERSION 3.30)
project (JoDWorldEditor)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_CXX_FLAGS "-flto=auto -pthread")
set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -fPIC ")
file(GLOB_RECURSE sources ../WorldEditorSource/**.cpp)
list(FILTER sources EXCLUDE REGEX ".*.inc.cpp$")
file(GLOB_RECURSE sources_shared ../../Shared/SharedWorldStructureSource/**.cpp ../../Shared/SharedCommonSource/**.cpp)
add_executable(JoDWorldEditor
    ${sources}
    ${sources_shared}
)
#target_include_directories(JoDServer PRIVATE ../ServerSource ../../Shared/SharedSource /usr/include/python3.12/)
target_include_directories(JoDWorldEditor PRIVATE ../WorldEditorSource ../../Shared/SharedWorldStructureSource ../../Shared/SharedCommonSource/ /usr/include/qt6)

target_precompile_headers(JoDWorldEditor PRIVATE ../WorldEditorSource/StdAfx/StdAfx.hpp)
#target_link_libraries(JoDServer python3.12)
target_link_libraries(JoDWorldEditor Qt6Core Qt6Widgets Qt6Gui)
