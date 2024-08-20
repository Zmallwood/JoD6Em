/*
 * StdAfx.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once
// External.
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket.hpp>
#include <json/json.h>
// Std.
#include <string>
#include <iostream>
#include <functional>
#include <map>
#include <any>
#include <thread>
#include <chrono>
#include <optional>
// Project.
#include "MathLib/MathConstants.hpp"
#include "MathLib/ColorF.hpp"
#include "MathLib/GLBoxF.hpp"
#include "MathLib/Point.hpp"
#include "MathLib/PointF.hpp"
#include "MathLib/Box.hpp"
#include "MathLib/BoxF.hpp"
#include "MathLib/Size.hpp"
#include "MathLib/SizeF.hpp"
#include "MathLib/Colors.hpp"
#include "Common/Aliases.hpp"
#include "CommonAliases.hpp"
#include "CommonUtils.hpp"
#include "Timer.hpp"
#include "NetConfiguration.hpp"
#include "WorldStructureAliases.hpp"
#include "WorldStructureConstants.hpp"