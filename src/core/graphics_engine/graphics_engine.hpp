/*
* Copyright (c) 2011-2014 Paul Wortmann
* General purpose, cross platform, computer game engine. [http://www.physhexgames.co.nr]
*
* This file is part of Project_0.
*
* Project_0 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* @author Paul Wortmann [paul.wortmann@gmail.com]
*
*/

#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <string>
#include "graphics_engine_vao_manager.hpp"

#define PROGRAM_NAME "Frost and Flame -> OpenGL 3.x+ test renderer."
#define RENDERER_GL1_CONTEXT_MAJOR 1
#define RENDERER_GL1_CONTEXT_MINOR 2
#define RENDERER_GL3_CONTEXT_MAJOR 3
#define RENDERER_GL3_CONTEXT_MINOR 3

#define RENDERER_GL1  1
#define RENDERER_GL3  3
#define RENDERER_GLES 64

struct render_GL_struct
{
    GLuint  vertexshader;
    GLuint  fragmentshader;
    GLuint  shaderprogram;
};

struct light_type
{
    float intensity_R;
    float intensity_G;
    float intensity_B;
    float intensity_A;
    bool  increase;
    float speed;
};

struct vertex_type
{
    float x;
    float y;
    float z;
};

struct vertex_texture_type
{
    float u;
    float v;
    float w;
};

struct vertex_normal_type
{
    float i;
    float j;
    float k;
};

class graphics_engine_class
{
    public:
        SDL_Window*       window;
        SDL_GLContext     context;
        SDL_DisplayMode  *display_mode;
        render_GL_struct  render_GL; // temp
        vao_manager_class vao_manager;
        int               gl_extention_count;
        std::string      *gl_extention_names;
        std::string       gl_version_string;
        std::string       gl_vendor_string;
        std::string       gl_renderer_string;
        std::string       gl_shading_language_version_string;
        int              *menu_mode_list;
        int               menu_mode_length;
        int               renderer;
        int               GL_major_version_number;
        int               GL_minor_version_number;
        int               current_display;
        int               current_display_mode;
        int               number_displays;
        int               number_display_modes;
        graphics_engine_class(void);
       ~graphics_engine_class(void);
        bool              init(void);
        bool              deinit(void);
        bool              render(void);
        bool              build_mode_list(void);
        std::string       get_display_mode(int mode_number);
};

int   gl_to_res(float gl_coord, int max_res);
float res_to_gl(int  res_coord, int max_res);
std::string pixel_format_from_int(int pfi);
#endif //GRAPHICS_ENGINE_H
