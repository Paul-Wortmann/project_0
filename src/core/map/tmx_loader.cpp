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

#include <iostream>
#include <fstream>
#include <string>

#include "tmx_loader.hpp"
#include "../../game.hpp"

extern game_class game;

void tmx_loader_class::load(map_class &map_pointer, std::string file_name)
{
    std::string   line;
    std::fstream file_handle;
    file_handle.open (file_name.c_str(), std::ios::in | std::ios::binary);
    if (file_handle.is_open())
    {
        while(getline(file_handle,line))
        {
            std::cout << line << '\n';
        }
        file_handle.close();
    }
    else game.core.log.write("FAIL -> Unable to load file"+file_name);
}




