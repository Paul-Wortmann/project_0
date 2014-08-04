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

#ifndef CORE_HPP
#define CORE_HPP

#include "graphics_engine/graphics_engine.hpp"
#include "map/map.hpp"
#include "map/loader_tmx.hpp"
#include "map/loader_xml.hpp"
#include "other/command_line_parser.hpp"
#include "other/config.hpp"
#include "other/debug.hpp"
#include "other/file.hpp"
#include "other/io_manager.hpp"
#include "other/log.hpp"
#include "other/misc.hpp"
#include "other/physics.hpp"
#include "other/timer.hpp"
#include "resource_management/font_manager.hpp"
#include "resource_management/music_manager.hpp"
#include "resource_management/object_manager.hpp"
#include "resource_management/sound_manager.hpp"
#include "resource_management/sprite_sheet_manager.hpp"
#include "resource_management/texture_manager.hpp"

class core_class
{
    public:
    //bool                       debug;
    unsigned int               FPS;
    command_line_parser_class  command_line_parser;
    config_class               config;
    debug_class                debug;
    file_class                 file;
    font_manager_class         font_manager;
    graphics_engine_class      graphics;
    io_manager_class           io_manager;
    loader_tmx_class           tmx_loader;
    loader_xml_class           xml_loader;
    log_class                  log;
    misc_class                 misc;
    music_manager_class        music_manager;
    object_manager_class       object_manager;
    physics_class              physics;
    sound_manager_class        sound_manager;
    sprite_sheet_manager_class sprite_sheet_manager;
    texture_manager_class      texture_manager;
    timer_class                timer;
};

#endif // CORE_HPP
