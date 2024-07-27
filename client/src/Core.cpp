// Copyright (c) 2024 Andreas Åkerberg.

#include "Core.h"
#include "Graphics.h"
#include "Net.h"
#include "Rendering.h"

namespace jod
{
    void RunNewClientInstance()
    {
        /* Access ClientEngine and run it. */
        _<ClientEngine>().Run();
    }

    namespace
    {
        void GameLoopFunction();
    }

    void ClientEngine::Run() const
    {
        /* Start network connection. */
        _<WebSocketClient>().Start();

        /* Required by SDL2 before using it. */
        SDL_Init(SDL_INIT_EVERYTHING);

        /* Touch Graphics to initialize it. */
        _<Graphics>();

        /* Start game loop. */
        auto simulateInfiniteLoop = 1;
        emscripten_set_main_loop(GameLoopFunction, 0, simulateInfiniteLoop);
    }

    void ClientEngine::PollEvents()
    {
        SDL_Event event;

        /* Poll for events from user every frame. */
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
            {
                /* Quit game by stopping ClientEngine. */
                m_running = false;
                break;
            }
            }
        }
    }

    RenderInstructionsManager::RenderInstructionsManager()
    {
        /* Create a sufficient amount of RIDs for drawing images and game start. */
        for (auto i = 0; i < k_maxNumDrawInstructions; i++)
            m_rids.push_back(_<ImageRenderer>().NewImage());
    }

    void RenderInstructionsManager::AddImageDrawInstruction(int imageNameHash, RectF dest)
    {
        /* Create a new image draw instruction and save it. */
        auto newInstruction = ImageDrawInstruction{m_rids.at(m_imageDrawInstructionsBuffer.size()),
                                                   imageNameHash, dest};
        m_imageDrawInstructionsBuffer.push_back(newInstruction);
    }

    void RenderInstructionsManager::ApplyBuffer()
    {
        /* Replace the current instruction group with the new one. */
        m_imageDrawInstructions = m_imageDrawInstructionsBuffer;

        /* Prepare the next-instructions-set for storing a new set
           of instructions by clearing it. */
        m_imageDrawInstructionsBuffer.clear();
    }

    void RenderInstructionsManager::ExecuteInstructions()
    {
        /* Execute all drawing instructions that have been added. */
        for (auto &instr : m_imageDrawInstructions)
            _<ImageRenderer>().DrawImage(instr.rid, instr.imageNameHash, instr.dest);
    }

    namespace
    {
        void GameLoopFunction()
        {
            /* Exit main loop if user has requested it. */
            if (!_<ClientEngine>().m_running)
                emscripten_cancel_main_loop();

            /* Poll user events and process them. */
            _<ClientEngine>().PollEvents();

            /* Clear canvas with single color to prepare for new rendering. */
            _<Graphics>().ClearCanvas();

            /* Request updated drawing requests from server. */
            _<WebSocketClient>().SendMessage("Tick");

            /* Draw canvas in its current state (current set of drawing instructions). */
            _<RenderInstructionsManager>().ExecuteInstructions();

            /* Present canvas to users web browser. */
            _<Graphics>().PresentCanvas();
        }
    }
}