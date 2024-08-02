// image_renderer.cpp
//
// Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
//

#include "image_renderer.h"
#include "client_core/assets/image_bank.h"
#include "math_lib.h"
#include "client_core/graphics/rendering/rendering_core/shader_program.h"

namespace jod {
    namespace {
        // Vertex shader for image rendering
        const GLchar *defaultShaderImagesVertex =
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
        // Fragment shader for image rendering
        const GLchar *defaultShaderImagesFragment =
            "#version 300 es\n"
            "precision mediump float;\n"
            "in vec4 ex_Color;\n"
            "in vec2 ex_TexCoord;\n"
            "in vec2 ex_Pos;\n"
            "out vec4 FragColor;\n"
            "uniform sampler2D TexUnit;\n"
            "void main() {\n"
            "    FragColor = texture(TexUnit, ex_TexCoord);\n"
            "}\0";
        constexpr int k_locPosition{0}; // Location of position variable in vertex shader.
        constexpr int k_locColor{1}; // Location of color variable in vertex shader.
        constexpr int k_locUv{2}; // Location of UV variable in vertex shader.
        int m_locNoPixelEffect{-1}; // Location of pixelation effect switch variable in vertex shader.
    }
    
    image_renderer::image_renderer(){
        // Create shader program.
        m_shaderProgram->create(
            defaultShaderImagesVertex,
            defaultShaderImagesFragment);
        // m_locNoPixelEffect = GetUniformLocation("noPixelEffect");
    }
    
    image_renderer::~image_renderer(){
        cleanup_base(); // Delete allocated resources for the renderer.
    }
    
    rid
    image_renderer::new_image(){
        auto rid = gen_new_vao_id(); // Create new Vertex Array Object.
        use_vao_begin(rid); // Use it.
        // Create buffers that are needed for 2D image rendering.
        auto indexBuffID = gen_new_buff_id(buffer_types::Indices, rid);
        auto posBuffID = gen_new_buff_id(buffer_types::Positions2D, rid);
        auto colorBuffID = gen_new_buff_id(buffer_types::Colors, rid);
        auto uvBuffID = gen_new_buff_id(buffer_types::UVs, rid);
        // Set buffers to empty data.
        set_indices_data(
            indexBuffID,
            math_constants::k_numVerticesInRectangle,
            nullptr);
        set_data(
            posBuffID,
            math_constants::k_numVerticesInRectangle,
            nullptr,
            buffer_types::Positions2D);
        set_data(
            colorBuffID,
            math_constants::k_numVerticesInRectangle,
            nullptr,
            buffer_types::Colors);
        set_data(
            uvBuffID,
            math_constants::k_numVerticesInRectangle,
            nullptr,
            buffer_types::UVs);
        use_vao_end(); // Stop using the Vertex Array Object.
        return rid; // Return the ID for the created VAO.
    }
    
    void
    image_renderer::draw_image(
        rid rid,
        int imageNameHash,
        const rectf &dest,
        bool repeatTexture,
        sizef textureFillAmount,
        colorf color){
        auto GLRect = dest.to_glrectf(); // Convert destination to GL coordinate system.
        // Create 4 vertices for an image rectangle.
        vertex2f verts[math_constants::k_numVerticesInRectangle];
        // Set vertices positions.
        verts[0].pos = {GLRect.x, GLRect.y - GLRect.h};
        verts[1].pos = {GLRect.x, GLRect.y};
        verts[2].pos = {GLRect.x + GLRect.w, GLRect.y};
        verts[3].pos = {GLRect.x + GLRect.w, GLRect.y - GLRect.h};
        // Set vertices texture coordinates.
        verts[0].uv = {0.0f, 1.0f / textureFillAmount.h};
        verts[1].uv = {0.0f, 0.0f};
        verts[2].uv = {1.0f / textureFillAmount.w, 0.0f};
        verts[3].uv = {1.0f / textureFillAmount.w, 1.0f / textureFillAmount.h};
        glDisable(GL_DEPTH_TEST); // No need for depth testing in a 2D plane.
        // Obtain GL ID for image to be rendered.
        auto imageID = _<image_bank>().get_image(imageNameHash);
        if (imageID == -1) return; // If requested image not found, stop the rendering.
        glBindTexture(GL_TEXTURE_2D, imageID); // Start use the image.
        // If we should repeat the texture as a pattern or fit it to the destination rectangle.
        if (repeatTexture){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }else{
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        // Create indices for the vertices.
        auto indices = std::vector<int>(
            math_constants::k_numVerticesInRectangle);
        std::iota(std::begin(indices), std::end(indices), 0);
        // Put render input into pure float vector format.
        std::vector<float> positions;
        std::vector<float> colors;
        std::vector<float> uvs;
        for (auto &vert : verts){
            positions.push_back(vert.pos.x);
            positions.push_back(vert.pos.y);
            colors.push_back(color.r);
            colors.push_back(color.g);
            colors.push_back(color.b);
            colors.push_back(color.a);
            uvs.push_back(vert.uv.x);
            uvs.push_back(vert.uv.y);
        }
        use_vao_begin(rid); // Start using the Vertex Array Object.
        auto noPixelEffect = true; // If pixelation effect should be used.
        // glUniform1f(m_locNoPixelEffect, noPixelEffect ? 1.0f : 0.0f);
        // Get buffer IDs for the required data contents.
        auto indexBuffID = get_buff_id(buffer_types::Indices, rid);
        auto posBuffID = get_buff_id(buffer_types::Positions2D, rid);
        auto colorBuffID = get_buff_id(buffer_types::Colors, rid);
        auto uvBuffID = get_buff_id(buffer_types::UVs, rid);
        // Provide the float vector data to the buffers.
        update_indices_data(indexBuffID, indices);
        update_data(
            posBuffID, positions, buffer_types::Positions2D,
            k_locPosition);
        update_data(colorBuffID, colors, buffer_types::Colors, k_locColor);
        update_data(uvBuffID, uvs, buffer_types::UVs, k_locUv);
        // Do the actual rendering.
        glDrawElements(
            GL_TRIANGLE_FAN,
            math_constants::k_numVerticesInRectangle, GL_UNSIGNED_INT, NULL);
        use_vao_end(); // Stop using the Vertex Array Object.
    }
    
    void
    image_renderer::draw_image(
        rid rid,
        std::string_view imageName,
        const rectf &dest,
        bool repeatTexture,
        sizef textureFillAmount,
        colorf color){
        // Forward the method call to the main overload.
        draw_image(
            rid, jod::hash(imageName), dest, repeatTexture,
            textureFillAmount, color);
    }
}