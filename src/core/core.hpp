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
#include "other/command_line_parser.hpp"
#include "other/config.hpp"
#include "other/file.hpp"
#include "other/io_manager.hpp"
#include "other/log.hpp"
#include "other/misc.hpp"
#include "other/timer.hpp"

class core_class
{
    public:
    bool                      debug;
    unsigned int              FPS;
    command_line_parser_class command_line_parser;
    config_class              config;
    file_class                file;
    graphics_engine_class     graphics;
    io_manager_class          io_manager;
    log_class                 log;
    misc_class                misc;
    timer_class               timer;
};

#endif // CORE_HPP
