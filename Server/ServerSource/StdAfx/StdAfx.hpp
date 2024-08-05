/*
 * StdAfx.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

// External.
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket.hpp>

// Std.
#include <string>
#include <iostream>
#include <functional>
#include <map>
#include <any>
#include <thread>
#include <chrono>
#include <mutex>

// Project.
#include "MathLib/MathConstants.hpp"
#include "MathLib/ColorF.hpp"
#include "MathLib/GLRectF.hpp"
#include "MathLib/Point.hpp"
#include "MathLib/PointF.hpp"
#include "MathLib/RectF.hpp"
#include "MathLib/Size.hpp"
#include "MathLib/SizeF.hpp"
#include "Common/Aliases.hpp"
#include "CommonUtils.hpp"
#include "NetConfiguration.hpp"
