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

#define OBJECT_AABB   0
#define OBJECT_CIRCLE 1

struct f3_type
{
    float x;
    float y;
    float z;
};

struct object_data_type
{
    int     type;
    f3_type position;
};

struct object_struct
{
    object_data_type data;
    //voa_data_type     *voa;
    //physics_data_type *physics_data;
};



class object_manager_class
{
    public:
    bool not_yet_implemented;
};

#endif // OBJECT_MANAGER_HPP
