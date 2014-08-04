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

#include <physfs.h>
#include <fstream>
#include <string>
#include "loader_xml.hpp"
#include "../../game.hpp"

extern game_class         game;

void loader_xml_class::load(xml_map_type *xml_map_pointer, std::string file_name)
{
    game.core.log.write("Loading XML map file -> "+file_name);
    if (PHYSFS_exists(file_name.c_str()))
    {
        PHYSFS_File *file_pointer = PHYSFS_openRead(file_name.c_str());
        if (file_pointer)
        {
            //code
            if (file_pointer) PHYSFS_close(file_pointer);
        }
        else
        {
            game.core.log.write("Fail -> PhysicsFS unable to open file - "+file_name);
        }
    }
    else
    {
        game.core.log.write("Fail -> PhysicsFS unable to find file - "+file_name);
    }
};

void loader_xml_class::save(xml_map_type *xml_map_pointer, std::string file_name)
{
};

