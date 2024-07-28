// Copyright (c) 2024 Andreas Åkerberg.

#pragma once

namespace jod
{
  /**
   * @brief Initializes and handles preparing and finilizing graphics for each frame.
   *
   */
  class Graphics
  {
   public:
    /**
     * @brief Construct a new Graphics object and initialize GLFW with OpenGL and applying
     *        needed settings.
     *
     */
    Graphics();

    /**
     * @brief Clear web browser before rendering new contents.
     *
     */
    void ClearCanvas();

    /**
     * @brief Present all rendered contents stored in the buffer.
     *
     */
    void PresentCanvas();

    /**
     * @brief GLFW window object.
     *
     */
    GLFWwindow *m_window = nullptr;

   private:
    /**
     * @brief Window title used if the game would be in desktop application format.
     *
     */
    const std::string k_title = "Journey of Dreams";
  };

  class Cursor
  {
   public:
    Cursor();

    void Render() const;

   private:
    RID m_ridCursorImage;
    const std::string k_cursorImageName = "CursorDefault";
    const float k_cursorSize = 0.03f;
  };
}