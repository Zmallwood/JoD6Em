// Copyright (c) 2024 Andreas Åkerberg.

#include "Core.h"
#include "Graphics.h"
#include "Net.h"
#include "Rendering.h"

namespace jod
{
    void RunNewClientInstance()
    {
        _<ClientEngine>().Run();
    }

    namespace
    {
        void GameLoopFunction()
        {
            if (!_<ClientEngine>().m_running)
                emscripten_cancel_main_loop();
            _<ClientEngine>().PollEvents();
            _<Graphics>().ClearCanvas();
            _<WebSocketClient>().SendMessage("Tick");
            _<Canvas>().DrawCanvas();
            _<Graphics>().PresentCanvas();
        }
    }

    void ClientEngine::Run()
    {
        _<WebSocketClient>().Start();
        SDL_Init(SDL_INIT_EVERYTHING);
        _<Graphics>();
        auto simulateInfiniteLoop = 1;
        emscripten_set_main_loop(GameLoopFunction, 0, simulateInfiniteLoop);
    }

    void ClientEngine::PollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
            {
                m_running = false;
                break;
            }
            }
        }
    }

    Canvas::Canvas()
    {
        for (auto i = 0; i < k_maxNumDrawInstructions; i++)
            m_rids.push_back(_<ImageRenderer>().NewImage());
    }

    void Canvas::AddImageDrawInstruction(int imageNameHash, RectF dest)
    {
        m_nextImageDrawInstructions.push_back({m_rids.at(m_nextImageDrawInstructions.size()), imageNameHash, dest});
    }

    void Canvas::PresentNewCanvas()
    {
        m_imageDrawInstructions = m_nextImageDrawInstructions;
        m_nextImageDrawInstructions.clear();
    }

    void Canvas::DrawCanvas()
    {
        for (auto &instr : m_imageDrawInstructions)
            _<ImageRenderer>().DrawImage(instr.m_rid, instr.m_imageNameHash, instr.m_dest);
    }
}