/*
 * RunGameServer.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {

///
/// Run the game server, called only once in the program.
///
/// @param argv The argv parameter from the main function,
///             contains the hostname and port number.
///
void RunGameServer(char **argv);

}