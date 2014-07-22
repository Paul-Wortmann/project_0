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

#ifndef SPRITE_SHEET_MANAGER_H
#define SPRITE_SHEET_MANAGER_H

#include <string>

struct sprite_sheet_data_type
{
    bool             loaded;
    std::string      file_name;
    unsigned int     data;
    float            texture_width;
    float            texture_height;
    float            angle;
    int              sprite_width;
    int              sprite_height;
    int              sprites_x;
    int              sprites_y;
    int              sprites_total;
};

struct sprite_sheet_type
{
    sprite_sheet_data_type  data;
    sprite_sheet_type      *next;
};

class sprite_sheet_manager_class
{
    public:
        sprite_sheet_manager_class(void);
       ~sprite_sheet_manager_class(void);
        int                number_of_sprite_sheets;
        sprite_sheet_type *root;
        sprite_sheet_type *last;
        sprite_sheet_type *add(std::string file_name, int width, int height);
        bool               load(sprite_sheet_type *sprite_sheet);
        void               draw(sprite_sheet_type *sprite_sheet, float pos_x, float pos_y, float pos_z, float width, float height, float angle, int sprite);
};

#endif // SPRITE_SHEET_MANAGER_H
