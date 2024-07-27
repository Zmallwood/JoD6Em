#pragma once

namespace jod
{
    void RunNewClientInstance();

    class ClientEngine
    {
      public:
        void Run();
        void PollEvents();

        bool m_running = true;
    };

    class ImageDrawInstruction
    {
      public:
        RID m_rid = -1;
        int m_imageNameHash = 0;
        RectF m_dest;
    };

    class Canvas
    {
      public:
        Canvas();
        void AddImageDrawInstruction(int imageNameHash, RectF dest);
        void PresentNewCanvas();
        void DrawCanvas();

      private:
        std::vector<ImageDrawInstruction> m_imageDrawInstructions;
        std::vector<ImageDrawInstruction> m_nextImageDrawInstructions;
        std::vector<RID> m_rids;
        const int k_maxNumDrawInstructions = 200;
    };
}