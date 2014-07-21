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

#include "music_manager.hpp"
#include "../../game.hpp"

extern game_class game;

music_manager_class::music_manager_class(void)
{
    music_manager_class::root            = NULL;
    music_manager_class::last            = NULL;
    music_manager_class::current         = NULL;
    music_manager_class::number_of_music = 0;
    music_manager_class::track           = 0;
    music_manager_class::next_track      = true;
};

music_manager_class::~music_manager_class(void)
{
    Mix_HaltMusic();
    music_type* temp_pointer;
    temp_pointer = music_manager_class::root;
    if (temp_pointer != NULL)
    {
        while (temp_pointer->next != NULL)
        {
            Mix_FreeMusic(temp_pointer->music_data);
            temp_pointer = temp_pointer->next;
        }
    }
};

bool music_manager_class::init(void)
{
    game.core.log.write("Initializing music manager.");
    bool return_value = true;
    int flags=MIX_INIT_OGG;
    flags=flags|MIX_INIT_FLAC;
    //flags=flags|MIX_INIT_MOD;
    int initted=Mix_Init(flags);
    if ((initted&flags) != flags)
    {
        game.core.log.write("Mix_Init: Failed to initialize support for all required sound formats!");
        game.core.log.write("Mix_Init: "+game.core.misc.cctos(Mix_GetError()));
        return_value = false;
    }
    else
    {
        const SDL_version *linked_version = Mix_Linked_Version();
        SDL_version compiled_version;
        SDL_MIXER_VERSION(&compiled_version);
        game.core.log.write("SDL_Mixer compiled version: "+game.core.misc.itos(compiled_version.major)+"."+game.core.misc.itos(compiled_version.minor)+"."+game.core.misc.itos(compiled_version.patch));
        game.core.log.write("SDL_Mixer Linked version:   "+game.core.misc.itos(linked_version->major)+"."+game.core.misc.itos(linked_version->minor)+"."+game.core.misc.itos(linked_version->patch));
    }
    return (return_value);
}

music_type *music_manager_class::add_music(std::string file_name)
{
    if (music_manager_class::number_of_music == 0)
    {
        music_manager_class::root = new music_type;
        music_manager_class::root->next = NULL;
        music_manager_class::last = new music_type;
        music_manager_class::last = root;
        music_manager_class::last->next = NULL;
    }
    else
    {
        music_type* temp_pointer;
        temp_pointer = music_manager_class::root;
        if (temp_pointer != NULL)
        {
            while (temp_pointer != NULL)
            {
                if (strcmp(file_name.c_str(),temp_pointer->path.c_str()) == 0) return(temp_pointer);
                temp_pointer = temp_pointer->next;
            }
        }
        music_manager_class::last->next = new music_type;
        music_manager_class::last = music_manager_class::last->next;
        music_manager_class::last->next = new music_type;
        music_manager_class::last->next = NULL;
    }
    music_manager_class::last->path = file_name.c_str();
    music_manager_class::last->loaded = music_manager_class::load_music(last);
    if (music_manager_class::last->loaded) music_manager_class::number_of_music++;
    return(music_manager_class::last);
};

bool music_manager_class::load_music(music_type *music)
{
    bool return_value = false;
    music->music_data = game.core.file.load_music(music->path.c_str());
    if (music->music_data != NULL) return_value = true;
    else game.core.log.write("Failed to load music ->"+music->path);
    return (return_value);
};

void music_manager_class::play(music_type *music)
{
    if (music->music_data != NULL)
    {
        if (Mix_PlayMusic(music->music_data,-1) == -1)
        {
            game.core.log.write("FAIL -> unable to play music -> "+music->path);
        }
    }
    else
    {
        game.core.log.write("FAIL -> unable to play music -> NULL pointer passed to play function.");
    }
};
