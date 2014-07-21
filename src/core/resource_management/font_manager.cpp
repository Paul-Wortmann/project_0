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

#include <sstream>
#include "font_manager.hpp"
#include "../../game.hpp"

extern game_class game;

font_manager_class::font_manager_class (void)
{
    font_manager_class::root            = NULL;
    font_manager_class::last            = NULL;
    font_manager_class::number_of_fonts = 0;
}

font_manager_class::~font_manager_class (void)
{
    font_type* temp_pointer;
    temp_pointer = font_manager_class::root;
    if (temp_pointer != NULL)
    {
        while (temp_pointer->next != NULL)
        {
            TTF_CloseFont(temp_pointer->font_data);
            if (temp_pointer->rwops_pointer) SDL_FreeRW(temp_pointer->rwops_pointer);
            if (temp_pointer->file_data) delete [] temp_pointer->file_data;
            temp_pointer = temp_pointer->next;
        }
    }
}

void font_manager_class::init(void)
{
    game.core.log.write("Initializing font manager.");
    if(!TTF_WasInit() && TTF_Init()==-1)
    {
        game.core.log.write("Fail -> TTF_Init: "+game.core.misc.cctos(TTF_GetError()));
    }
    const SDL_version *linked_version = TTF_Linked_Version();
    SDL_version compiled_version;
    SDL_TTF_VERSION(&compiled_version);
    game.core.log.write("SDL_TTF compiled version: "+game.core.misc.itos(compiled_version.major)+"."+game.core.misc.itos(compiled_version.minor)+"."+game.core.misc.itos(compiled_version.patch));
    game.core.log.write("SDL_TTF Linked version:   "+game.core.misc.itos(linked_version->major)+"."+game.core.misc.itos(linked_version->minor)+"."+game.core.misc.itos(linked_version->patch));
}

void font_manager_class::deinit(void)
{
    if (TTF_WasInit()) TTF_Quit();
}

font_type *font_manager_class::add_font (std::string file_name)
{
    if (font_manager_class::number_of_fonts == 0)
    {
        font_manager_class::root = new font_type;
        font_manager_class::root->next = NULL;
        font_manager_class::last = new font_type;
        font_manager_class::last = root;
        font_manager_class::last->next = NULL;
    }
    else
    {
        font_type* temp_pointer;
        temp_pointer = font_manager_class::root;
        if (temp_pointer != NULL)
        {
            while (temp_pointer != NULL)
            {
                if (strcmp(file_name.c_str(),temp_pointer->path.c_str()) == 0) return(temp_pointer);
                temp_pointer = temp_pointer->next;
            }
        }
        font_manager_class::last->next = new font_type;
        font_manager_class::last = font_manager_class::last->next;
        font_manager_class::last->next = new font_type;
        font_manager_class::last->next = NULL;
    }
    font_manager_class::last->path          = file_name.c_str();
    font_manager_class::last->loaded = font_manager_class::load_font(last);
    if (font_manager_class::last->loaded)
    {
        font_manager_class::number_of_fonts++;
        return (font_manager_class::last);
    }
    else
    {
        game.core.log.write("Fail - Font manager function, add font -> "+file_name);
        return (font_manager_class::last);
    }
}

bool font_manager_class::load_font (font_type *font, int pt_size)
{
    bool return_value   = false;
    game.core.file.load_font(font,pt_size);
    if (font->font_data != NULL)
    {
        //game.core.log.write("Loaded font -> ",font->path.c_str());
        return_value = true;
    }
    else game.core.log.write("Failed to load font -> "+font->path);
    return (return_value);
}

bool font_manager_class::load_font (font_type *font)
{
    return (font_manager_class::load_font (font, 48));
}
