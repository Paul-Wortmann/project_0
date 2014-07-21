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

#ifndef FILE_H
#define FILE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../resource_management/font_manager.hpp"

struct file_buffer_type
{
    char *data;
    int   buffer_size;
};

class file_class
{
    public:
         file_class(void);
        ~file_class(void);
        std::string       file_path;
        bool              extension_exist           (std::string file_name);
        bool              extension_exist           (std::string file_name, std::string file_extension);
        std::string       extension_add             (std::string file_name, std::string file_extension);
        std::string       extension_remove          (std::string file_name);
        std::string       path_get                  (std::string file_name);
        std::string       path_remove               (std::string file_name);
        std::string       path_add                  (std::string file_name, std::string path_name);
        char             *filetobuf                 (std::string file_name);
        void              file_system_path          (std::string file_name);
        void              file_system_init          (char** arg_data);
        void              file_system_deinit        (void);
        SDL_Surface      *load_image                (std::string file_name);
        void              load_font                 (font_type *font, int pt_size);
        Mix_Music        *load_music                (std::string file_name);
        Mix_Chunk        *load_sound                (std::string file_name);
        char             *load_file_to_buffer       (std::string file_name);
        file_buffer_type *load_file_to_buffer_object(std::string file_name);
        std::string       get_time_string           (void);
};


#endif //FILE_H

