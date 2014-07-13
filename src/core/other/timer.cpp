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

#include "SDL2/SDL.h"
#include "timer.hpp"

timer_class::timer_class()
{
	timer_class::running    = false;
	timer_class::ready      = false;
	timer_class::startticks = 0;
}

timer_class::~timer_class()
{
}

void timer_class::start()
{
	if (!timer_class::running)
	{
		timer_class::running = true;
		timer_class::startticks = SDL_GetTicks();
	}
}

void timer_class::stop()
{
	if (timer_class::running)
	{
		timer_class::running = false;
	}
}

unsigned int timer_class::getticks()
{
    if (timer_class::running) return(SDL_GetTicks() - timer_class::startticks);
    else return(0);
}

