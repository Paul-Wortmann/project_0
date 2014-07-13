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

#ifndef CONFIG_H
#define CONFIG_H

#include <SDL2/SDL.h>
#include <string>

struct system_info_type
{
    std::string platform;
    int         CPU_count;
    int         CPU_cache_line_size;
    int         system_RAM;
    bool        has_3DNow;
    bool        has_AVX;
    bool        has_AltiVec;
    bool        has_MMX;
    bool        has_RDTSC;
    bool        has_SSE;
    bool        has_SSE2;
    bool        has_SSE3;
    bool        has_SSE41;
    bool        has_SSE42;
};

class config_class
{
    private:
    public:
        std::string      file_name;
        system_info_type system_info;
        int              display_resolution;
        int              display_resolution_x;
        int              display_resolution_y;
        int              display_bpp;
        bool             display_fullscreen;
        bool             display_touchscreen;
        int              display_flags;
        int              font_base_resolution_x;
        int              font_base_resolution_y;
        float            font_scale_x;
        float            font_scale_y;
        bool             mouse_autohide;
        int              mouse_autohide_timer;
        int              mouse_autohide_timer_count;
        int              menu_delay;
        int              menu_delay_count;
        int              mouse_resolution_x;
        int              mouse_resolution_y;
        int              joystick_sensitivity;
        bool             joystick_enabled;
        int              joystick_no_buttons;
        int              audio_rate;
        int              audio_channels;
        int              audio_buffers;
        int              audio_volume_music;
        int              audio_volume_sound;
        std::string      language;
                         config_class(void);
                        ~config_class(void);
        void             set_defaults(void);
        bool             file_set(std::string file_name_in);
        bool             file_write(std::string data_string);
        bool             file_load(void);
        bool             file_save(void);
        bool             file_clear(void);
        bool             file_delete(void);
        void             mouse_autohide_process(bool set_active);
        void             get_system_information(void);
        void             log_system_information(void);
        void             log_config_information(void);
};

#endif //CONFIG_H
