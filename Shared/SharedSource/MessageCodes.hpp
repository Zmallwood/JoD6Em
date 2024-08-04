/*
 * MessageCodes.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    namespace MessageCodes {
        constexpr int k_draw_image_instr = 1;
        
        constexpr int k_apply_buffer = 2;
        
        constexpr int k_left_mouse_down = 3;
        
        constexpr int k_canvas_size = 4;
        
        constexpr int k_mouse_position = 5;
        
        constexpr int k_frame_finished = 6;
        
        constexpr int k_draw_string_instr = 7;
        
        constexpr int k_right_mouse_down = 8;
    }
}