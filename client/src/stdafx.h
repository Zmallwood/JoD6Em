// Copyright (c) 2024 Andreas Åkerberg.
#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <emscripten/emscripten.h>
#include <emscripten/websocket.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <map>
#include <filesystem>
#include <numeric>
#include <string>

#include "math_lib.h"
#include "util.h"
#include "common_utils.h"
#include "net_configuration.h"