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

#include "file.hpp"
#include "../../game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <physfs.h>

extern game_class game;

file_class::file_class (void)
{
    file_class::file_path  = GAME_NAME;
    file_class::file_path += ".dat";
};

file_class::~file_class (void)
{

};

bool file_class::extension_exist (std::string file_name, std::string file_extension)
{
    int file_size = (int)file_name.size();
    if ((file_extension[0] == file_name[file_size-3]) &&
        (file_extension[1] == file_name[file_size-2]) &&
        (file_extension[2] == file_name[file_size-1])) return (true);
    else return (false);
};

bool file_class::extension_exist (std::string file_name)
{
    bool extention_found = false;
    for (int string_pos = 0; string_pos < (int)file_name.size(); string_pos++)
    {
        if (file_name[string_pos] == '.') extention_found = true;
    }
    return (extention_found);
};

std::string file_class::extension_add (std::string file_name, std::string file_extension)
{
    if (file_extension[0] == '.') return (file_name+file_extension);
    else return (file_name+'.'+file_extension);
};

std::string file_class::extension_remove (std::string file_name)
{
    bool            extention_found = false;
    std::string     temp_string     = "";
    for (int string_pos = 0; string_pos < (int)file_name.size(); string_pos++)
    {
        if (file_name[string_pos] == '.') extention_found = true;
        if (!extention_found) temp_string += file_name[string_pos];
    }
    return (temp_string);
};

std::string file_class::path_get (std::string file_name)
{
    int         slash_count = 0;
    int         slash_pos   = 0;
    std::string temp_string = "";
    for (int string_pos = 0; string_pos < (int)file_name.size(); string_pos++)
    {
        if (file_name[string_pos] == '/') slash_count++;
    }
    for (int string_pos = 0; string_pos < (int)file_name.size(); string_pos++)
    {
        if (slash_pos < slash_count)
        {
            temp_string += file_name[string_pos];
        }
        if (file_name[string_pos] == '/') slash_pos++;
    }
    return (temp_string);
};

std::string file_class::path_remove (std::string file_name)
{
    int             slash_position  = -1;
    std::string     temp_string     = "";
    for (int string_pos = 0; string_pos < (int)file_name.size(); string_pos++)
    {
        if (file_name[string_pos] == '\\') slash_position = string_pos;
        if (file_name[string_pos] == '/') slash_position = string_pos;
    }
    for (int string_pos = slash_position+1; string_pos < (int)file_name.size(); string_pos++)
    {
        temp_string += file_name[string_pos];
    }
    return (temp_string);
};

std::string file_class::path_add (std::string file_name, std::string path_name)
{
    return (path_name+file_name);
};

char* file_class::filetobuf (std::string file_name)
{
    FILE *file_pointer;
    long length;
    char *buf;
    file_pointer = fopen(file_name.c_str(), "rb");
    if (!file_pointer)
    {
        game.core.log.write("Failed to load file into buffer -> "+file_name);
        return NULL;
    }
    fseek(file_pointer, 0, SEEK_END);
    length = ftell(file_pointer);
    buf = (char*)malloc(length+1);
    fseek(file_pointer, 0, SEEK_SET);
    fread(buf, length, 1, file_pointer);
    fclose(file_pointer);
    buf[length] = 0;
    return buf;
}

void file_class::file_system_path(std::string file_name)
{
    file_class::file_path = file_name;
}

void file_class::file_system_init(char** arg_data)
{
    game.core.log.write("Initializing Physics File System.");
    PHYSFS_init(arg_data[0]);
    PHYSFS_Version version_info;
    PHYSFS_getLinkedVersion(&version_info);
    game.core.log.write("PhysFS Version -> "+game.core.misc.itos(version_info.major)+"."+game.core.misc.itos(version_info.minor)+"."+game.core.misc.itos(version_info.patch));
    int load_error = PHYSFS_addToSearchPath(file_class::file_path.c_str(), 1);
    if (load_error != 1)
    {
        game.core.log.write("Fail -> Unable to load game data file: "+game.core.misc.itos(load_error));
        game.state = GAME_STATE_ERROR;
    }
}

void file_class::file_system_deinit(void)
{
    game.core.log.write("Shutting down Physics File System.");
    PHYSFS_deinit();
}

SDL_Surface * file_class::load_image(std::string file_name)
{
    SDL_Surface *temp_serface = NULL;
    if (PHYSFS_exists(file_name.c_str()))
    {
        PHYSFS_openRead(file_name.c_str());
        PHYSFS_File *file_pointer = NULL;
        file_pointer = PHYSFS_openRead(file_name.c_str());
        if (file_pointer)
        {
            PHYSFS_sint64 file_size = PHYSFS_fileLength(file_pointer);
            char *file_data = new char[file_size];
            PHYSFS_read(file_pointer, file_data, 1, file_size);
            SDL_RWops *rwops_pointer = NULL;
            rwops_pointer = SDL_RWFromMem(file_data, file_size);
            if (rwops_pointer != NULL)
            {
                temp_serface  = IMG_Load_RW(rwops_pointer, false);
                if (rwops_pointer) SDL_FreeRW(rwops_pointer);
            }
            else
            {
                game.core.log.write("Fail -> PhysicsFS unable to allocate rwops pointer for file - "+file_name);
            }
            if (file_data) delete [] file_data;
            if (file_pointer) PHYSFS_close(file_pointer);
        }
        else
        {
            game.core.log.write("Fail -> PhysicsFS unable to open file - "+file_name);
        }
    }
    else
    {
        game.core.log.write("Fail -> PhysicsFS unable to find file - "+file_name);
    }
    if (!temp_serface) game.state = GAME_STATE_ERROR;
    return(temp_serface);
}

/*
void file_class::load_font(font_type *font, int pt_size)
{
    if (PHYSFS_exists(font->path.c_str()))
    {
        PHYSFS_openRead(font->path.c_str());
        PHYSFS_File *file_pointer = NULL;
        file_pointer = PHYSFS_openRead(font->path.c_str());
        if (file_pointer)
        {
            PHYSFS_sint64 file_size = PHYSFS_fileLength(file_pointer);
            font->file_data = new char[file_size];
            PHYSFS_read(file_pointer, font->file_data, 1, file_size);
            font->rwops_pointer = SDL_RWFromMem(font->file_data, file_size);
            if (font->rwops_pointer != NULL)
            {
                font->font_data = TTF_OpenFontRW(font->rwops_pointer, false,pt_size);
                if (!font->font_data) game.core.log.write("Fail -> TTF_OpenFontRW: "+game.core.misc.itos(TTF_GetError()));
            }
            else
            {
                game.core.log.write("Fail -> PhysicsFS unable to allocate rwops pointer for file - "+font->path);
            }
            if (file_pointer) PHYSFS_close(file_pointer);
        }
        else
        {
            game.core.log.write("Fail -> PhysicsFS unable to open file - "+font->path);
        }
    }
    else
    {
        game.core.log.write("Fail -> PhysicsFS unable to find file - "+font->path);
    }
    if (!font->font_data) game.state = GAME_STATE_ERROR;
}
*/

Mix_Music *file_class::load_music(std::string file_name)
{
    std::string string_data;
    Mix_Music *temp_music = NULL;
    if (PHYSFS_exists(file_name.c_str()))
    {
        PHYSFS_openRead(file_name.c_str());
        PHYSFS_File *file_pointer = NULL;
        file_pointer = PHYSFS_openRead(file_name.c_str());
        if (file_pointer)
        {
            PHYSFS_sint64 file_size = PHYSFS_fileLength(file_pointer);
            char *file_data = new char[file_size];
            PHYSFS_read(file_pointer, file_data, 1, file_size);
            SDL_RWops *rwops_pointer = NULL;
            rwops_pointer = SDL_RWFromMem(file_data, file_size);
            if (rwops_pointer != NULL)
            {
                temp_music  = Mix_LoadMUS_RW(rwops_pointer, false);
                if (!temp_music)
                {
                    string_data  = "FAIL -> Mix_LoadMUS :";
                    string_data += Mix_GetError();
                    game.core.log.write(string_data);
                }
                if (rwops_pointer) SDL_FreeRW(rwops_pointer);
            }
            else
            {
                game.core.log.write("Fail -> PhysicsFS unable to allocate rwops pointer for file - "+file_name);
            }
            if (file_data) delete [] file_data;
            if (file_pointer) PHYSFS_close(file_pointer);
        }
        else
        {
            game.core.log.write("Fail -> PhysicsFS unable to open file - "+file_name);
        }
    }
    else
    {
        game.core.log.write("Fail -> PhysicsFS unable to find file - "+file_name);
    }
    if (!temp_music) game.state = GAME_STATE_ERROR;
    return(temp_music);
}

Mix_Chunk *file_class::load_sound(std::string file_name)
{
    Mix_Chunk *temp_sound = NULL;
    if (PHYSFS_exists(file_name.c_str()))
    {
        PHYSFS_openRead(file_name.c_str());
        PHYSFS_File *file_pointer = NULL;
        file_pointer = PHYSFS_openRead(file_name.c_str());
        if (file_pointer)
        {
            PHYSFS_sint64 file_size = PHYSFS_fileLength(file_pointer);
            char *file_data = new char[file_size];
            PHYSFS_read(file_pointer, file_data, 1, file_size);
            SDL_RWops *rwops_pointer = NULL;
            rwops_pointer = SDL_RWFromMem(file_data, file_size);
            if (rwops_pointer != NULL)
            {
                temp_sound  = Mix_LoadWAV_RW(rwops_pointer, false);
                if (rwops_pointer) SDL_FreeRW(rwops_pointer);
            }
            else
            {
                game.core.log.write("Fail -> PhysicsFS unable to allocate rwops pointer for file - "+file_name);
            }
            if (file_data) delete [] file_data;
            if (file_pointer) PHYSFS_close(file_pointer);
        }
        else
        {
            game.core.log.write("Fail -> PhysicsFS unable to open file - "+file_name);
        }
    }
    else
    {
        game.core.log.write("Fail -> PhysicsFS unable to find file - "+file_name);
    }
    if (!temp_sound) game.state = GAME_STATE_ERROR;
    return(temp_sound);
}

char *file_class::load_file_to_buffer (std::string file_name)
{
    char *temp_buffer = NULL;
    if (PHYSFS_exists(file_name.c_str()))
    {
        PHYSFS_openRead(file_name.c_str());
        PHYSFS_File *file_pointer = NULL;
        file_pointer = PHYSFS_openRead(file_name.c_str());
        if (file_pointer)
        {
            PHYSFS_sint64 file_size = PHYSFS_fileLength(file_pointer);
            temp_buffer = new char[file_size+1];
            int length_read = PHYSFS_read(file_pointer, temp_buffer, 1, file_size);
            temp_buffer[file_size] = 0; // added for GL shader loading
            if (file_size != length_read)
            {
                game.core.log.write("Fail -> PhysicsFS ERROR loading file into buffer - "+file_name);
                game.core.log.write("   File size - "+ game.core.misc.itos((int)file_size)+" data length read into buffer - "+ game.core.misc.itos(length_read));
            }
            if (file_pointer) PHYSFS_close(file_pointer);
        }
        else
        {
            game.core.log.write("Fail -> PhysicsFS unable to open file - "+file_name);
        }
    }
    else
    {
        game.core.log.write("Fail -> PhysicsFS unable to find file - "+file_name);
    }
    if (temp_buffer == NULL)
    {
        game.core.log.write("Fail -> PhysicsFS unable to load file into buffer - "+file_name);
        game.state = GAME_STATE_ERROR;
    }
    return(temp_buffer);
}

std::string file_class::get_time_string(void)
{
    time_t rawtime;
    rawtime = time(&rawtime);
    char buffer [80];
    #ifdef __MINGW32__
        strftime (buffer,80,"%Y-%m-%d - %H:%M:%S - %Z",localtime(&rawtime));
    #else
        struct tm newtime;
        strftime (buffer,80,"%Y-%m-%d - %H:%M:%S - %Z",localtime_r(&rawtime, &newtime));
    #endif
    return(buffer);
}
