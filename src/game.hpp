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

#ifndef GAME_HPP
#define GAME_HPP

#include "core/core.hpp"
#include "core/map/map.hpp"

#define GAME_NAME "Project_0"
#define GAME_VERSION_MAJOR 0
#define GAME_VERSION_MINOR 0
#define GAME_VERSION_PATCH 1

#define GAME_STATE_INIT   0
#define GAME_STATE_ACTIVE 1
#define GAME_STATE_DEINIT 2
#define GAME_STATE_QUIT   3
#define GAME_STATE_ERROR  4

class game_class
{
    public:
    int        state;
    core_class core;
    map_class  map;
    void       init(void);
    void       write_log_version(void);
    void       write_console_version(void);
    void       deinit(void);
};

#endif // GAME_HPP
