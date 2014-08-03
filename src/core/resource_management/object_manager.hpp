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

#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

#include "../other/types.hpp"
#include "sprite_sheet_manager.hpp"
#define OBJECT_AABB   0
#define OBJECT_CIRCLE 1

struct object_texture_data_type
{
    sprite_sheet_type *difuse;
    sprite_sheet_type *normal;
    sprite_sheet_type *specular;
};

struct object_base_data_type
{
    int                      UID;
    bool                     loaded;
    int                      type;
    f3_type                  position;
    f3_type                  dimention; //AABB
    f3_type                  rotation;
};

struct object_render_data_type
{
    object_texture_data_type  texture;
    f3_type                  *vertex;
};

struct object_physics_data_type
{
    f3_type *velocity;
    f3_type *acceleration;
};

struct object_type
{
    object_base_data_type   base;
    object_render_data_type render;
    //physics_data_type      *physics_data;
    object_type            *next;
};



class object_manager_class
{
    public:
        object_manager_class(void);
       ~object_manager_class(void);
        int                number_of_objects;
        object_type       *root;
        object_type       *last;
        object_type       *add(int UID);
};

#endif // OBJECT_MANAGER_HPP
