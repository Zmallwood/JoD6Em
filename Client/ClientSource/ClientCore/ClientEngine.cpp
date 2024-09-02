/*
 * ClientEngine.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ClientEngine.hpp"
#include "ClientCore/Graphics/Graphics.hpp"
#include "MessageCodes.hpp"
#include "ClientCore/Net/WSServerConnection.hpp"
#include "DrawInstructions/DrawInstrMngr.hpp"
#include "Input/SetupInputCallbacks.hpp"
#include "Utilities/ClientFPSCounter.hpp"

namespace JoD {
namespace {
    void GameLoopFunction();
}

void ClientEngine::Run() const {
    _<WSServerConnection>().Connect();
    SDL_Init(SDL_INIT_EVERYTHING);
    SetupInputCallbacks();
    _<Graphics>();
    const auto simulateInfiniteLoop = 1;
    emscripten_set_main_loop(GameLoopFunction, 125, simulateInfiniteLoop);
}

namespace {
    void GameLoopFunction() {
        if (!_<ClientEngine>().GetRunning())
            emscripten_cancel_main_loop();
        _<ClientFPSCounter>().Update();
        _<WSServerConnection>().SendMessage(
            MessageCodes::k_mousePosition);
        _<Graphics>().ClearCanvas();
        _<DrawInstrMngr>().ExecAllInstr();
        _<ClientFPSCounter>().Render();
        _<Graphics>().PresentCanvas();
    }
}
}