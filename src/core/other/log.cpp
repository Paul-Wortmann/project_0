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

#include "log.hpp"
#include "../../game.hpp"

extern game_class game;

void log_class::clear(void)
{
    log_class::file_handle.open(log_class::file_name.c_str(),std::ios::out|std::ios::binary|std::ios::trunc);
    if (log_class::file_handle.is_open()) log_class::file_handle.close();
    else std::cout << "FAIL -> Unable to open log file" << std::endl;
}

void log_class::init(void)
{
    log_class::clear();
    log_class::file_handle.open (log_class::file_name.c_str(), std::ios::out | std::ios::app);
    if (!log_class::file_handle.is_open()) std::cout << "FAIL -> Unable to open log file" << std::endl;
    else
    {
        log_class::write("# " + game.core.misc.cctos(GAME_NAME) + " #");
        log_class::write("# ---------------------------------------------- #");
        log_class::write("# Log file created: "+game.core.file.get_time_string());
        log_class::write("");
    }
}

void log_class::deinit(void)
{
    if (log_class::file_handle.is_open()) log_class::file_handle.close();
}

void log_class::write(std::string data)
{
    if (log_class::file_handle.is_open()) log_class::file_handle << data << std::endl;
    else  std::cout << "FAIL -> Unable to write to log file" << std::endl;
}
