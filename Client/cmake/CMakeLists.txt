cmake_minimum_required (VERSION 3.30)
project (JourneyOfDreams)
set (CMAKE_CXX_STANDARD 20)
set (CXX_STANDARD_REQUIRED ON)
set(CMAKE_TOOLCHAIN_FILE $ENV{EMSDK_HOME}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
set(CMAKE_EXECUTABLE_SUFFIX ".html")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-flto=auto -sUSE_SDL=2 -sUSE_SDL_TTF=2 -sUSE_SDL_IMAGE=2 -sUSE_WEBGL2=1 -sSTB_IMAGE -sUSE_GLFW=3 --preload-file ${CMAKE_SOURCE_DIR}/../preloaded_files@/ --shell-file ${CMAKE_SOURCE_DIR}/../html/shell_minimal.html")
file(GLOB_RECURSE sources ../ClientSource/**.cpp)
file(GLOB_RECURSE sources_shared ../../Shared/SharedSource/**.cpp)
add_executable(JourneyOfDreams 
    ${sources}
    ${sources_shared}
)
target_include_directories(JourneyOfDreams PRIVATE ../ClientSource ../../Shared/SharedSource)

target_precompile_headers(JourneyOfDreams PRIVATE ../ClientSource/StdAfx/stdafx.h)
target_link_libraries(JourneyOfDreams websocket.js)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(COMMAND ${CMAKE_CXX_COMPILER} --cflags -sUSE_SDL=2 -sUSE_SDL_TTF=2
    OUTPUT_VARIABLE EM_CFLAGS
    COMMAND_ERROR_IS_FATAL ANY
)
string(STRIP "${EM_CFLAGS}" EM_CFLAGS)
find_package(Python3 REQUIRED)
message("Python: ${Python3_EXECUTABLE}")
set(ENV{EXTRA_FLAGS} "${EM_CFLAGS}")
execute_process(
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/fix_compile_commands.py
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
