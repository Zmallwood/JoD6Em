// Copyright (c) 2024 Andreas Åkerberg.
#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/websocket.hpp>
#include <thread>

#include <string>
#include <iostream>
#include <functional>
#include <map>

#include "math_lib.h"
#include "common_utils.h"
#include "net_configuration.h"
#include "math.h"