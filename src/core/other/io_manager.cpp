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

#include "io_manager.hpp"
#include "../../game.hpp"

extern game_class game;

void io_manager_class::init(void)
{
    io_manager_class::key_escape = false;
};

void io_manager_class::process(void)
{
    while (SDL_PollEvent(&event))
    {
        //std::cout << "Event ->n" << io_manager_class::event.type << "\n";
        switch(io_manager_class::event.type)
        {
            case SDL_QUIT:
                io_manager_class::key_escape = true;
            break;
            case SDL_WINDOWEVENT:
                switch(io_manager_class::event.window.event)
                {
                    case SDL_WINDOWEVENT_ENTER:
                    break;
                    case SDL_WINDOWEVENT_LEAVE:
                    break;
                    default:
                        //game.core.log.write("FAIL -> io_manager unable to process window event: "+game.core.misc.itos(io_manager_class::event.window.event));
                    break;
                }
            break;
            case SDL_KEYDOWN:
                switch(io_manager_class::event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        io_manager_class::key_escape = true;
                    break;
                    default:
                        game.core.log.write("FAIL -> io_manager unable to process keydown: "+game.core.misc.itos(io_manager_class::event.key.keysym.sym));
                    break;
                }
            break;
            case SDL_KEYUP:
                switch(io_manager_class::event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        io_manager_class::key_escape = false;
                    break;
                    default:
                        game.core.log.write("FAIL -> io_manager unable to process keyup: "+game.core.misc.itos(io_manager_class::event.key.keysym.sym));
                    break;
                }
            break;
            default:
                //game.core.log.write("FAIL -> io_manager unable to process event: "+game.core.misc.itos(io_manager_class::event.type));
            break;
        }
    }
};

