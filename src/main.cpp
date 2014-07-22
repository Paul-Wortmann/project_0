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

#include <iostream>
#include <stdlib.h>
#include "physfs.h"

#include "game.hpp"

game_class game;

int main (int argc, char **argv)
{
    sprite_sheet_type *test_sprite_sheet = NULL;
    texture_type *test_texture  = NULL;
    texture_type *test_tile_set = NULL;
    tmx_map_type *test_map      = NULL;
    unsigned int return_value = EXIT_SUCCESS;
    while (game.state != GAME_STATE_QUIT)
    {
        switch (game.state)
        {
            case GAME_STATE_INIT:
                game.init();
                game.core.log.write("# -------------- Game initialization ------------ #");
                //game.core.debug = true;
                game.write_console_version();
                game.core.config.file_load();
                game.core.command_line_parser.process(argc,argv);
                game.core.config.log_system_information();
                game.core.config.log_config_information();
                game.core.file.file_system_path(game.core.misc.cctos(GAME_NAME)+".dat");
                game.core.file.file_system_init(argv);
                //----------------- temp debug ---------------------
                game.core.config.display_fullscreen   = false;
                game.core.config.display_resolution_x = 640;
                game.core.config.display_resolution_y = 480;
                //----------------- temp debug ---------------------
                game.core.graphics.renderer = RENDERER_GL1;
                game.core.graphics.init();
                SDL_Init(SDL_INIT_TIMER);
                game.core.timer.start();
                game.core.timer.last_ticks = game.core.timer.getticks();
                //init subsystems
                //load base resources
                //test_sprite_sheet  = game.core.sprite_sheet_manager.add("data/hello_karl.png",64,64);
                //test_tile_set = game.core.texture_manager.add_texture("data/tilesets/tileset_0.png",true,64,64);
                //test_texture = game.core.texture_manager.add_texture("data/tilesets/tileset_0.png",true,64,64);
                //game.core.tmx_loader.load(test_map,"data/maps/test_0.tmx");

                game.state = GAME_STATE_ACTIVE;
                game.core.log.write("# ---------------- Game started ----------------- #");
            break;
            case GAME_STATE_ACTIVE:
                game.core.FPS += (game.core.timer.getticks() - game.core.timer.last_ticks) / 1000;
                game.core.FPS /= 2;
                if ((game.core.timer.getticks() - game.core.timer.last_ticks) >= 1000/1)
                {
                    game.core.timer.last_ticks = game.core.timer.getticks();
                    game.core.timer.ready = true;
                }
                else if (!game.core.timer.ready) game.core.timer.ready = false;
                //timer
                //process
                game.core.io_manager.process();
                if (game.core.io_manager.key_escape) game.state = GAME_STATE_DEINIT;
                //render


//test-------------
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //game.core.sprite_sheet_manager.draw(test_sprite_sheet,0,0,0,1.0,0.5,0,0);
    SDL_GL_SwapWindow(game.core.graphics.window);
//test-------------



                //game.core.graphics.render();
            break;
            case GAME_STATE_DEINIT:
                game.core.log.write("# -------------- Game de-initialization --------- #");
                game.core.log.write("Textures loaded -> "+game.core.misc.itos(game.core.texture_manager.number_of_textures));
                game.core.log.write("Average FPS - "+game.core.misc.itos(game.core.FPS));
                if (return_value == EXIT_SUCCESS) game.core.log.write("Game terminated correctly.");
                else  game.core.log.write("Game terminated with error.");
                game.core.graphics.deinit();
                game.core.config.file_save();
                game.deinit();
                game.state = GAME_STATE_QUIT;
            break;
            case GAME_STATE_QUIT:
                //This code should never run! ;)
                game.core.log.write("FAIL -> Internal error!");
            break;
            case GAME_STATE_ERROR:
            default:
                game.core.log.write("FAIL -> Internal error!");
                return_value = EXIT_FAILURE;
                game.state = GAME_STATE_DEINIT;
            break;
        }
    }
    return (return_value);
}
