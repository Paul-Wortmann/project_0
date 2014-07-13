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

#ifndef VAO_MANAGER_H
#define VAO_MANAGER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>

#define VAO_ID_NONE -1

struct texture_data
{
    bool         loaded;
    std::string  file_name;
    unsigned int data;
};

struct vao_data_type
{
    unsigned int     vao_id;
    bool             loaded;
    bool             enabled;
    unsigned int     vao_data;
    unsigned int    *vbo_data;
    int              number_of_vertex;
    int              number_of_vbo;
    texture_data     texture_diffuse;
    texture_data     texture_specular;
    texture_data     texture_normal;
    GLfloat         *vertex;
    GLfloat         *color;
};

struct vao_type
{
    vao_data_type data;
    vao_type*     next;
};

class vao_manager_class
{
    public:
        vao_manager_class(void);
       ~vao_manager_class(void);
        int           number_of_vaos;
        vao_type *root;
        vao_type *last;
        vao_type *add_vao(vao_data_type *vao_data_pointer);
        bool      load_vao(vao_type *vao_pointer);
};

#endif // VAO_MANAGER_H
