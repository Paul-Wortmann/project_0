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

#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

struct font_type
{
    bool            loaded;
    std::string     path;
    TTF_Font       *font_data;
    SDL_RWops      *rwops_pointer;
    char           *file_data;
    font_type      *next;
};

class font_manager_class
{
    public:
        font_manager_class(void);
       ~font_manager_class(void);
        int           number_of_fonts;
        font_type    *root;
        font_type    *last;
        font_type    *add_font(std::string file_name);
        void          init(void);
        void          deinit(void);
        bool          load_font(font_type *font);
        bool          load_font(font_type *font, int pt_size);
};

#endif // FONT_MANAGER_H
