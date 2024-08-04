/*
 * StdAfx.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

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
#include "MathLib.hpp"
#include "Common/Aliases.hpp"
#include "Common/FileUtilities.hpp"
#include "Common/CanvasUtilities.hpp"
#include "Common/MouseUtilities.hpp"
#include "Common/SDLDeleter.hpp"
#include "CommonUtils.hpp"
#include "NetConfiguration.hpp"