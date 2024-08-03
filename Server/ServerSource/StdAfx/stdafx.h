/*
 * stdafx.h
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
#include "math_lib.h"
#include "common_utils.h"
#include "net_configuration.h"
#include "math.h"
#include "Expression/expr_return_struct.h"
#include "Expression/expr.h"