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

#ifndef LOADER_XML_H
#define LOADER_XML_H

#include "../resource_management/texture_manager.hpp"
#include "../other/types.hpp"

struct xml_object_data_type
{
    bool loaded;
};

struct xml_map_type
{
    xml_object_data_type* object;
};

class loader_xml_class
{
    public:
    void load(xml_map_type* xml_map_pointer, std::string file_name);
    void save(xml_map_type* xml_map_pointer, std::string file_name);
};

#endif //LOADER_XML_H
