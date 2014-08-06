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
#include "debug.hpp"
#include "../core.hpp"
#include "../../game.hpp"

extern game_class game;

debug_class::debug_class (void)
{
    debug_class::enabled         = true;
    debug_class::enabled_console = true;
    debug_class::enabled_log     = true;
    debug_class::enabled_msgbox  = true;
}

debug_class::~debug_class (void)
{

}

void debug_class::write(std::string message)
{
    if (debug_class::enabled_console) std::cout << message << std::endl;
    if (debug_class::enabled_log)     game.core.log.write(message);
    if (debug_class::enabled_msgbox)  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Internal Error.",message.c_str(),NULL);
}

void debug_class::write(std::string message, int flags)
{
    if (flags == FLAG_DEBUG_CONSOLE) std::cout << message << std::endl;
    if (flags == FLAG_DEBUG_LOG)     game.core.log.write(message);
    if (flags == FLAG_DEBUG_MSGBOX)  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Internal Error.",message.c_str(),NULL);
}
