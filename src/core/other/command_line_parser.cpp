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

#include <string>
#include "command_line_parser.hpp"
#include "../../game.hpp"

extern game_class game;

void command_line_parser_class::process (int arg_count, char** arg_data)
{
    std::string temp_string;
    command_line_parser_class::number_of_args = arg_count;
    for (int arg_number = 0; arg_number < arg_count; arg_number++)
    {
        temp_string = arg_data[arg_number];
        if ((temp_string.compare("--help") == 0) ||
            (temp_string.compare("-help") == 0) ||
            (temp_string.compare("-h") == 0))
        {
            std::cout << "-d   Enable developer mode." << std::endl;
            std::cout << "-h   This help screen." << std::endl;
            std::cout << "-v   Version information." << std::endl;
            std::cout << "-w   Enable a windowed mode." << std::endl;
        }
        else if ((temp_string.compare("--version") == 0) ||
            (temp_string.compare("-version") == 0) ||
            (temp_string.compare("-v") == 0))
        {
            game.write_console_version();
        }
        else
        {
            if ( arg_number > 0) std::cout << GAME_NAME << temp_string.c_str() << std::endl;
        }
    }
};


