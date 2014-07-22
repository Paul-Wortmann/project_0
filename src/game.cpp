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

#include "game.hpp"

void game_class::init(void)
{
    game_class::state = GAME_STATE_INIT;
    game_class::core.debug = false;
    game_class::core.log.file_name = GAME_NAME;
    game_class::core.log.file_name += ".log";
    game_class::core.config.file_name = GAME_NAME;
    game_class::core.config.file_name += ".cfg";
    game_class::core.log.init();
    game_class::core.io_manager.init();
}

void game_class::deinit(void)
{
    game_class::core.file.file_system_deinit();
    game_class::core.log.deinit();
}

void game_class::write_log_version(void)
{
    game_class::core.log.write(game_class::core.misc.cctos(GAME_NAME)+" - Version "+game_class::core.misc.itos(GAME_VERSION_MAJOR)+"."+game_class::core.misc.itos(GAME_VERSION_MINOR)+"."+game_class::core.misc.itos(GAME_VERSION_PATCH));
}

void game_class::write_console_version(void)
{
    std::cout << game_class::core.misc.cctos(GAME_NAME) << " - Version " << game_class::core.misc.itos(GAME_VERSION_MAJOR) << "." << game_class::core.misc.itos(GAME_VERSION_MINOR) << "." << game_class::core.misc.itos(GAME_VERSION_PATCH) << std::endl;
}
