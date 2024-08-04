/*
 * StdAfx.hpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

// External.
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket.hpp>
#include <thread>
#include <chrono>

// Std.
#include <string>
#include <iostream>
#include <functional>
#include <map>
#include <any>

// Project.
#include "Common/Aliases.hpp"
#include "MathLib.hpp"
#include "CommonUtils.hpp"
#include "NetConfiguration.hpp"