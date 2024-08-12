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
#include "NetConfiguration.hpp"
#include "MathLib/MathConstants.hpp"
#include "MathLib/ColorF.hpp"
#include "MathLib/GLBoxF.hpp"
#include "MathLib/Point.hpp"
#include "MathLib/PointF.hpp"
#include "MathLib/BoxF.hpp"
#include "MathLib/Size.hpp"
#include "MathLib/SizeF.hpp"
#include "MathLib/Colors.hpp"
#include "Common/Aliases.hpp"
#include "Common/FileUtilities.hpp"
#include "Common/CanvasUtilities.hpp"
#include "Common/MouseUtilities.hpp"
#include "Common/SDLDeleter.hpp"
#include "CommonUtils.hpp"
#include "CommonAliases.hpp"