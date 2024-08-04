/*
 * ImageRenderer.cpp
 * 
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "ImageRenderer.h"
#include "ClientCore/Assets/ImageBank.h"
#include "MathLib.h"
#include "ClientCore/Graphics/Rendering/RenderingCore/ShaderProgram.h"

namespace JoD {
    namespace {
        // Vertex shader for image rendering
        const GLchar *default_shader_images_vertex =
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
        const GLchar *default_shader_images_fragment =
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
        constexpr int k_loc_position{0}; // Location of position variable in vertex shader.
        constexpr int k_loc_color{1}; // Location of color variable in vertex shader.
        constexpr int k_loc_uv{2}; // Location of UV variable in vertex shader.
        int m_loc_no_pixel_effect{-1}; // Location of pixelation effect switch variable in vertex shader.
    }
    
    ImageRenderer::ImageRenderer(){
        // Create shader program.
        m_shader_program->Create(
            default_shader_images_vertex,
            default_shader_images_fragment); 
        // m_locNoPixelEffect = GetUniformLocation("noPixelEffect");
    }
    
    ImageRenderer::~ImageRenderer(){
        CleanupBase(); // Delete allocated resources for the renderer.
    }
    
    RID ImageRenderer::NewImage() {
        auto rid = GenNewVAOID(); // Create new Vertex Array Object.
        UseVAOBegin(rid); // Use it.
        // Create buffers that are needed for 2D image rendering.
        auto index_buff_id = GenNewBuffID(BufferTypes::indices, rid);
        auto pos_buff_id = GenNewBuffID(BufferTypes::positions_2d, rid);
        auto color_buff_id = GenNewBuffID(BufferTypes::colors, rid);
        auto uv_buff_id = GenNewBuffID(BufferTypes::uvs, rid);
        // Set buffers to empty data.
        SetIndicesData(
            index_buff_id,
            MathConstants::k_num_vertices_in_rectangle,
            nullptr);
        SetData(
            pos_buff_id,
            MathConstants::k_num_vertices_in_rectangle,
            nullptr,
            BufferTypes::positions_2d);
        SetData(
            color_buff_id,
            MathConstants::k_num_vertices_in_rectangle,
            nullptr,
            BufferTypes::colors);
        SetData(
            uv_buff_id,
            MathConstants::k_num_vertices_in_rectangle,
            nullptr,
            BufferTypes::uvs);
        UseVAOEnd(); // Stop using the Vertex Array Object.
        return rid; // Return the ID for the created VAO.
    }
    
    void ImageRenderer::DrawImage(
        RID rid,
        int image_name_hash,
        const RectF &destination,
        bool repeat_texture,
        SizeF texture_fill_amount,
        ColorF color){
        auto gl_rect = destination.to_glrectf(); // Convert destination to GL coordinate system.
        // Create 4 vertices for an image rectangle.
        Vertex2F verts[MathConstants::k_num_vertices_in_rectangle];
        // Set vertices positions.
        verts[0].pos = {gl_rect.x, gl_rect.y - gl_rect.h};
        verts[1].pos = {gl_rect.x, gl_rect.y};
        verts[2].pos = {gl_rect.x + gl_rect.w, gl_rect.y};
        verts[3].pos = {gl_rect.x + gl_rect.w, gl_rect.y - gl_rect.h};
        // Set vertices texture coordinates.
        verts[0].uv = {0.0f, 1.0f / texture_fill_amount.h};
        verts[1].uv = {0.0f, 0.0f};
        verts[2].uv = {1.0f / texture_fill_amount.w, 0.0f};
        verts[3].uv = {1.0f / texture_fill_amount.w,
                       1.0f / texture_fill_amount.h};
        glDisable(GL_DEPTH_TEST); // No need for depth testing in a 2D plane.
        // Obtain GL ID for image to be rendered.
        auto image_id = _<ImageBank>().GetImage(image_name_hash);
        if (image_id == -1) return; // If requested image not found, stop the rendering.
        glBindTexture(GL_TEXTURE_2D, image_id); // Start use the image.
        // If we should repeat the texture as a pattern or fit it to the destination rectangle.
        if (repeat_texture){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }else{
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        // Create indices for the vertices.
        auto indices = std::vector<int>(
            MathConstants::k_num_vertices_in_rectangle);
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
        UseVAOBegin(rid); // Start using the Vertex Array Object.
        auto no_pixel_effect = true; // If pixelation effect should be used.
        // glUniform1f(m_locNoPixelEffect, noPixelEffect ? 1.0f : 0.0f);
        // Get buffer IDs for the required data contents.
        auto index_buff_id = GetBuffID(BufferTypes::indices, rid);
        auto pos_buff_id = GetBuffID(BufferTypes::positions_2d, rid);
        auto color_buff_id = GetBuffID(BufferTypes::colors, rid);
        auto uv_buff_id = GetBuffID(BufferTypes::uvs, rid);
        // Provide the float vector data to the buffers.
        UpdateIndicesData(index_buff_id, indices);
        UpdateData(
            pos_buff_id, positions, BufferTypes::positions_2d,
            k_loc_position);
        UpdateData(color_buff_id, colors, BufferTypes::colors, k_loc_color);
        UpdateData(uv_buff_id, uvs, BufferTypes::uvs, k_loc_uv);
        // Do the actual rendering.
        glDrawElements(
            GL_TRIANGLE_FAN,
            MathConstants::k_num_vertices_in_rectangle, GL_UNSIGNED_INT, NULL);
        UseVAOEnd(); // Stop using the Vertex Array Object.
    }
    
    void ImageRenderer::DrawImage(
        RID rid,
        std::string_view image_name,
        const RectF &destination,
        bool repeat_texture,
        SizeF texture_fill_amount,
        ColorF color){
        // Forward the method call to the main overload.
        DrawImage(
            rid, Hash(image_name), destination, repeat_texture,
            texture_fill_amount, color);
    }
}