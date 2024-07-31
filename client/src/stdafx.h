// Copyright (c) 2024 Andreas Åkerberg.
#pragma once
// External.
#include <SDL.h>
#include <SDL_ttf.h>
#include <emscripten/emscripten.h>
#include <emscripten/websocket.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>
// Std.
#include <iostream>
#include <memory>
#include <map>
#include <filesystem>
#include <numeric>
#include <string>
// Project.
#include "math_lib.h"
#include "util.h"
#include "common_utils.h"
#include "net_configuration.h"