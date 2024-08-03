/*
 * message_codes.h
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace jod {
    namespace message_codes {
        constexpr int k_draw_image_instr = 1;
        constexpr int k_apply_buffer = 2;
        constexpr int k_mouse_down = 3;
        constexpr int k_canvas_size = 4;
        constexpr int k_mouse_position = 5;
        constexpr int k_frame_finished = 6;
        constexpr int k_draw_string_instr = 7;
    }
}