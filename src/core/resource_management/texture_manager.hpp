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

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "font_manager.hpp"

#define GL_BGR  0x80E0
#define GL_BGRA 0x80E1

#define DEFAULT_FRAME_WIDTH     64
#define DEFAULT_FRAME_HEIGHT    32

#define TEXTURE_NONE            0
#define TEXTURE_IMAGE           1
#define TEXTURE_SPRITESHEET     2
#define TEXTURE_STRING          3

#define TEXTURE_RENDER_CENTERED 0
#define TEXTURE_RENDER_LEFT     1
#define TEXTURE_RENDER_RIGHT    2
#define TEXTURE_RENDER_UP       4
#define TEXTURE_RENDER_DOWN     8


struct frame_type
{
    bool         active;
    unsigned int data;
};

struct text_color_type
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

struct text_data_type
{
    std::string      text_string;
    float            text_size;
    text_color_type  color;
    font_type*       font;
};

struct texture_data_type
{
    bool             loaded;
    int              texture_flag;
    int              render_positioning;
    std::string      path;
    float            width;
    float            height;
    bool             rotate_able;
    float            rotate_speed;
    int              rotate_direction;
    float            angle;
    float            frame_delay;
    float            frame_delay_count;
    float            frame_delay_max;
    int              frame_number;
    int              frame_max;
    frame_type*      frame;
    text_data_type   text;
};

struct texture_type
{
    texture_data_type data;
    texture_type*     next;
};

class texture_manager_class
{
    public:
        texture_manager_class(void);
       ~texture_manager_class(void);
        int           number_of_textures;
        texture_type *root;
        texture_type *last;
        texture_type *add_texture(std::string file_name);
        texture_type *add_texture(std::string file_name, bool is_sprite_sheet);
        texture_type *add_texture(std::string file_name, bool is_sprite_sheet, int width_set, int height_set);
        texture_type *add_texture(std::string file_name, int width_set, int height_set, int texture_flag);
        texture_type *add_texture(font_type* font, std::string text_string, float text_size, int width_set, int height_set, int texture_flag);
        texture_type *add_texture(font_type* font, std::string text_string, float text_size, int width_set, int height_set, int r, int g, int b, int a, int texture_flag);
        void          load_textures(void);
        void          reload_textures(void);
        void          reload_texture(texture_type *texture);
        bool          load_texture(texture_type *texture);
        bool          load_sprite_sheet(texture_type *texture);
        bool          load_sprite_sheet(texture_type *texture, int width_set, int height_set);
        bool          load_string(texture_type *texture);
        bool          load_string(texture_type *texture_pointer, font_type* font_pointer, std::string text_string, float text_size, int r, int g, int b, int a);
        bool          load_string(texture_type *texture_pointer, font_type* font_pointer, std::string text_string, float text_size, int r, int g, int b, int a, int render_position);
        void          bind_image(texture_type *texture);
        void          process(texture_type *texture);
        void          draw(texture_type *texture, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set);
        void          draw(texture_type *texture, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, int   angle_set);
        void          draw(texture_type *texture, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, float angle_set);
        void          draw(texture_type *texture, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, float angle_set, float alpha);
        void          draw(texture_type *texture, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, float angle_set, float red, float green, float blue, float alpha);
        void          draw(texture_type *texture, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, float angle_set, float red, float green, float blue, float alpha, int frame_set);
        void          draw(texture_type *texture, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, float angle_set, int frame_set);
};

#endif // TEXTURE_MANAGER_H

