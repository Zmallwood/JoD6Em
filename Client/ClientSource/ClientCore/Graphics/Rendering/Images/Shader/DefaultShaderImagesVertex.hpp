/*
 * DefaultShaderImagesVertex.hpp
 *
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
    
    // Vertex shader for image rendering
    inline static const GLchar *g_defaultShaderImagesVertex =
        "#version 300 es\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec4 in_Color;\n"
        "layout (location = 2) in vec2 in_TexCoord;\n"
        "out vec4 ex_Color;\n"
        "out vec2 ex_TexCoord;\n"
        "out vec2 ex_Pos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   ex_Color = in_Color;\n"
        "   ex_TexCoord = in_TexCoord;\n"
        "   ex_Pos = aPos.xy;\n"
        "}\0";
}